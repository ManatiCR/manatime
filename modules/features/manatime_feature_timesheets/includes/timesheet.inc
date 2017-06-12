<?php

/**
 * @file
 * Template file for timesheet.
 */

 /**
  * Class timesheet.
  */
class Timesheet {

  private $node;
  private $uid;
  private $timeEntries;
  private $projects;
  private $status;
  private $records;

  /**
   * Construct.
   */
  public function __construct($node) {
    $this->node = $node;
    $this->uid = $this->node->uid;
    $this->status = $this->node->status;
    $this->records = array();
    $this->timeEntries = array();
    $this->projects = array();

    $this->fillTimeEntries();
    $this->fillProjects();
  }

  /**
   * Get nid.
   *
   * @return object
   *   The node timesheet.
   */
  public function getNode() {
    return $this->node;
  }

  /**
   * Set status.
   *
   * @param int $status
   *   The timesheet status, published or not published, possible values 1 or 0.
   */
  public function setStatus($status) {
    $this->status = $status;
  }

  /**
   * Get status.
   *
   * @return int
   *   The timesheet status, published or not published.
   */
  public function getStatus() {
    return $this->status;
  }

  /**
   * Get uid.
   *
   * @return int
   *   The timesheet user's id owner.
   */
  public function getUid() {
    return $this->uid;
  }

  /**
   * Set time_entries.
   */
  public function fillTimeEntries() {
    if (isset($this->node->field_time_entries[LANGUAGE_NONE])) {
      $result = $this->node->field_time_entries[LANGUAGE_NONE];
      $nids = array();
      foreach ($result as $record) {
        $nids[] = $record['target_id'];
      }
      $this->timeEntries = node_load_multiple($nids);
    }
    else {
      $this->timeEntries = array();
    }
  }

  /**
   * Add time_entry.
   */
  public function addTimeEntry($description, $duration, $project_id, $task_id, $date) {
    global $user;
    $entity = entity_create('node', array('type' => 'time_entries'));
    $entity->uid = $user->uid;
    $wrapper = entity_metadata_wrapper('node', $entity);
    $wrapper->title = 'time_entry';
    $wrapper->body->value = $description;
    $wrapper->field_duration = $duration;
    $wrapper->field_project = $project_id;
    $wrapper->field_task = $task_id;
    $wrapper->field_date->value = $date;
    $wrapper->field_date->value2 = $date;
    $wrapper->save();
    $this->node->field_time_entries[LANGUAGE_NONE][] = array(
      'target_id' => $wrapper->getIdentifier(),
    );
    node_save($this->node);
    $this->fillTimeEntries();
    $this->fillProjects();
  }

  /**
   * Edit time_entry.
   */
  public function editTimeEntry($entry, $description, $duration) {
    $wrapper = entity_metadata_wrapper('node', $entry);
    $wrapper->body->value = $description;
    $wrapper->field_duration = $duration;
    $wrapper->save();
  }

  /**
   * Get time_entries.
   *
   * @return array
   *   The timesheet's time entries.
   */
  public function getTimeEntries() {
    return $this->timeEntries;
  }

  /**
   * Get time_entries array.
   *
   * @return array
   *   The timesheet's time entries array.
   */
  public function getTimeEntriesArray($time_entries) {
    $time_entries_array = array();
    foreach ($time_entries as $time_entry) {
      $time_entry = entity_metadata_wrapper('node', $time_entry);
      $time_entries_array[] = array(
        'project' => $time_entry->field_project->label(),
        'task' => $time_entry->field_task->label(),
        'description' => $time_entry->body->value->value(),
        'duration' => $time_entry->field_duration->value(),
      );
    }
    return $time_entries_array;
  }

  /**
   * Set projects.
   */
  public function fillProjects() {
    if (isset($this->timeEntries)) {
      $nids = array();
      foreach ($this->timeEntries as $record) {
        $nids[] = $record->field_project[LANGUAGE_NONE][0]['target_id'];
      }
      $this->projects = node_load_multiple(array_unique($nids));
    }
    else {
      $this->projects = array();
    }
  }

  /**
   * Get blocked projects.
   *
   * When all the project's tasks has been reported, the
   * project will be blocked.
   *
   * @return array
   *   Only the blocked projects.
   */
  public function getBlockedProjects() {
    $list = array();
    if (isset($this->projects)) {
      foreach ($this->projects as $project) {
        $blocked = TRUE;
        $nids = $project->field_tasks[LANGUAGE_NONE];
        foreach ($nids as $nid) {
          if (empty($this->getTimeEntriesPerTask($nid['target_id']))) {
            $blocked = FALSE;
          }
        }
        if ($blocked) {
          $list[] = $project->nid;
        }
      }
    }
    return $list;
  }

  /**
   * Block new rows.
   *
   * Block the function to add new rows in the timesheet weekly view, when all
   * the timesheet's projects are blocked.
   */
  public function blockNewRows() {
    if (isset($this->projects)) {
      $blocked_projects = $this->getBlockedProjects();
      if ($this->getAllProjects() == $blocked_projects) {
        return TRUE;
      }
    }
    return FALSE;
  }

  /**
   * Get projects.
   *
   * @return array
   *   All projects.
   */
  public function getAllProjects() {
    $query = new EntityFieldQuery();
    // Get only active projects with tasks.
    $result = $query
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'projects')
      ->fieldCondition('field_active', 'value', 1, '=')
      ->fieldCondition('field_tasks', 'target_id', 'NULL', '!=')
      ->execute();
    if (isset($result['node'])) {
      return array_keys($result['node']);
    }
    return array();
  }

  /**
   * Get time_entries per day.
   *
   * @param string $date
   *   A date to filter the time entries per date, possible value: a date with
   *   format 'Y-m-d'.
   *
   * @return array
   *   Only entries with a date equal to $date value.
   */
  public function getTimeEntriesPerDay($date, $time_entries) {
    $entries = array();
    foreach ($time_entries as $entry) {
      $entry_date = $entry->field_date[LANGUAGE_NONE][0]['value'];
      $entry_date = date('Y-m-d', strtotime($entry_date));
      $date = date('Y-m-d', strtotime($date));
      if ($entry_date === $date) {
        $entries[] = $entry;
      }
    }
    return $entries;
  }

  /**
   * Get time_entries per task.
   *
   * @param int $id_task
   *   A node task's id.
   *
   * @return array
   *   Only entries with a task's id equal to $id_task value.
   */
  public function getTimeEntriesPerTask($id_task) {
    $entries = array();
    foreach ($this->timeEntries as $entry) {
      if ($entry->field_task[LANGUAGE_NONE][0]['target_id'] == $id_task) {
        $entries[] = $entry;
      }
    }
    return $entries;
  }

  /**
   * Get time_entries per project.
   *
   * @param int $id_project
   *   A node project's id.
   *
   * @return array
   *   Only entries with a project's id equal to $id_project value.
   */
  public function getTimeEntriesPerProject($id_project) {
    $node = node_load($id_project);
    $tasks = $node->field_tasks[LANGUAGE_NONE];
    $entries = array();
    foreach ($tasks as $task) {
      $list_entries = $this->getTimeEntriesPerTask($task['target_id']);
      if (!empty($list_entries)) {
        $entries[$task['target_id']] = $list_entries;
      }
    }
    return $entries;
  }

  /**
   * Get time_entries per project.
   *
   * @param int $id_project
   *   A node project's id.
   *
   * @return array
   *   Only tasks with a project's id equal to $id_project value.
   */
  public function getTasksPerProject($id_project) {
    $this->fillTimeEntries();
    $node = node_load($id_project);
    $list_tasks = $node->field_tasks[LANGUAGE_NONE];
    $nids = array();
    foreach ($list_tasks as $nid) {
      if (!empty($this->getTimeEntriesPerTask($nid['target_id']))) {
        $nids[] = $nid['target_id'];
      }
    }
    return node_load_multiple($nids);
  }

  /**
   * Returns the records in an array.
   *
   * A record is an array wich contain the row's values: project name, task
   * name, time entries, total hours worked and a link to remove it.
   */
  public function generateRecords() {
    $this->records = array();
    foreach ($this->projects as $project) {
      $tasks = $this->getTasksPerProject($project->nid);
      // Get the tasks of this project.
      foreach ($tasks as $task) {
        $task_entries = $this->getTimeEntriesPerTask($task->nid);
        $hours_worked = $this->getHoursWorked($task_entries);
        $remove_link_row = manatime_feature_timesheet_make_link_remove_row($this->node,
        $task->nid);
        $this->addRecord($project, $task, $task_entries,
        $hours_worked, $remove_link_row);
      }
    }
  }

  /**
   * Returns the task's entries separate per day.
   *
   * @param string $project
   *   A object type project.
   * @param string $task
   *   A object type task.
   * @param int $task_entries
   *   An array with the task's time entries.
   */
  public function getTaskEntriesPerDays($project, $task, $task_entries) {
    $record_entries = array();
    foreach ($this->getTimesheetDays() as $date) {
      $day_entries = $this->getTimeEntriesPerDay($date, $task_entries);
      // The day's time entry.
      if (!empty($day_entries)) {
        $entry = reset($day_entries);
        $text_title = check_plain($entry->body[LANGUAGE_NONE][0]['value']);
        $text_link = check_plain($entry->field_duration[LANGUAGE_NONE][0]['value']);
        $parameters = array(
          'time_entry_id' => $entry->nid,
        );
        $link_entry = manatime_feature_timesheet_modal_entry_link($this->node,
        $parameters, $text_link, $text_title);
      }
      else {
        $parameters = array(
          'project_id' => $project->nid,
          'task_id' => $task->nid,
          'date' => check_plain(strtotime($date)),
        );
        $link_entry = manatime_feature_timesheet_modal_entry_link($this->node,
        $parameters);
      }
      $record_entries[] = $link_entry;
    }
    return $record_entries;
  }

  /**
   * Return array with the timesheet's dates.
   *
   * @return array
   *   The timesheet's dates.
   */
  public function getTimesheetDays() {
    $timesheet_days = array();
    $beginning = $this->node->field_date['und'][0]['value'];
    $end = $this->node->field_date['und'][0]['value2'];
    for ($date = $beginning; $date <= $end;
      $date = date("Y-m-d H:i:s", strtotime($date . "+ 1 days"))) {
      $day_name = date("l", strtotime($date));
      $timesheet_days[$day_name] = date("Y-m-d H:i:s", strtotime($date));
    }
    return $timesheet_days;
  }

  /**
   * Return an array with the headers of the timesheet view.
   */
  public function getTimesheetViewHeaders() {
    $table_headers = array();
    $table_headers[] = t('Description');
    $day_names = array_keys($this->getTimesheetDays());
    foreach ($day_names as $day_name) {
      $table_headers[] = t('@dayname', array('@dayname' => $day_name));
    }
    $table_headers[] = t('Total');
    return $table_headers;
  }

  /**
   * Return the links for the daily view navegation.
   */
  public function getTimesheetDaysLinks() {
    $day_links = array();
    foreach ($this->getTimesheetDays() as $dayname => $day) {
      $day = date("Ymd", strtotime($day));
      $day_links[] = $previous_timesheet = l(t('@dayname', array('@dayname' => $dayname)), 'timesheet/daily/' . $day);
    }
    return $day_links;
  }

  /**
   * Get records.
   *
   * @return array
   *   The records to create the rows in the timesheet weekly view.
   */
  public function getRecords() {
    return $this->records;
  }

  /**
   * Add record.
   *
   * @param string $project
   *   A project name.
   * @param string $task
   *   A task name.
   * @param array $time_entries
   *   All task's time entries.
   * @param int $total_hours_worked
   *   Total hours'worked in a task.
   * @param string $remove_link_row
   *   A link to remove the record.
   */
  public function addRecord($project, $task, $time_entries, $total_hours_worked, $remove_link_row) {
    $this->records[] = array(
      'project' => check_plain($project->title),
      'task' => check_plain($task->title),
      'time_entries' => $this->getTaskEntriesPerDays($project, $task, $time_entries),
      'total_hours_worked' => check_plain($total_hours_worked),
      'remove_link_row' => $remove_link_row,
    );
  }

  /**
   * Remove record.
   *
   * @param int $task_id
   *   The task's id to delete.
   */
  public function removeRecord($task_id) {
    $task_entries = $this->getTimeEntriesPerTask($task_id);
    $nids = array();
    foreach ($task_entries as $entry) {
      $nids[] = $entry->nid;
    }
    if (!empty($nids)) {
      node_delete_multiple($nids);
    }
  }

  /**
   * Get time_entries per task.
   *
   * @param array $time_entries
   *   The time entries to consult.
   *
   * @return array
   *   The total hours worked.
   */
  public function getHoursWorked($time_entries) {
    $hours_worked = 0;
    foreach ($time_entries as $entry) {
      $hours_worked += $entry->field_duration[LANGUAGE_NONE][0]['value'];
    }
    return $hours_worked;
  }

  /**
   * Timesheet submit.
   */
  public function submit() {
    $this->fillTimeEntries();
    if (!empty($this->timeEntries)) {
      foreach ($this->timeEntries as $entry) {
        $entry->field_status[LANGUAGE_NONE][0]['value'] = 1;
        node_save($entry);
      }
    }
    $this->node->status = 1;
    node_save($this->node);
  }

}
