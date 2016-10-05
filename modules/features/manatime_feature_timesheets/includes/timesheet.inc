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
  public function addTimeEntry($description, $duration, $id_project, $id_task, $date) {
    global $user;
    $entity = entity_create('node', array('type' => 'time_entries'));
    $entity->uid = $user->uid;
    $wrapper = entity_metadata_wrapper('node', $entity);
    $wrapper->title = 'time_entry';
    $wrapper->body->value = $description;
    $wrapper->field_duration = $duration;
    $wrapper->field_project = $id_project;
    $wrapper->field_task = $id_task;
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
   * Get time_entries.
   *
   * @return array
   *   The timesheet's time entries.
   */
  public function getTimeEntries() {
    return $this->timeEntries;
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
   * Get projects.
   *
   * @return array
   *   All timesheet's projects.
   */
  public function getProjects() {
    return $this->projects;
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
  public function getTimeEntriesPerDay($date) {
    $entries = array();
    foreach ($this->timeEntries as $entry) {
      if ($entry->field_date[LANGUAGE_NONE][0]['value'] === $date) {
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
    $this->fillTimeEntries();
    foreach ($this->projects as $project) {
      $tasks = $this->getTasksPerProject($project->nid);
      // Get the tasks of this project.
      foreach ($tasks as $task) {
        $record_entries = array();
        $time_entries = $this->getTimeEntriesPerTask($task->nid);
        // Get the entries of this task.
        $total_hours_worked = 0;
        foreach ($time_entries as $time_entry) {
          $record_entry = array(
            'description' => t('@duration hrs @description', array(
              '@duration' => $time_entry->field_duration[LANGUAGE_NONE][0]['value'],
              '@description' => $time_entry->body[LANGUAGE_NONE][0]['value'],
            )),
            'duration' => $time_entry->field_duration[LANGUAGE_NONE][0]['value'],
          );
          $total_hours_worked += $time_entry->field_duration[LANGUAGE_NONE][0]['value'];
          // Get the number day.
          $timestamp = strtotime($time_entry->field_date[LANGUAGE_NONE][0]['value']);
          $number_day = date('N', $timestamp);
          if (isset($record_entries[$number_day])) {
            $record_entries[$number_day][0]['duration'] += check_plain($record_entry['duration']);
            $record_entries[$number_day][0]['description'] = check_plain($record_entries[$number_day][0]['description'] . ' ' . $record_entry['description']);
          }
          else {
            $record_entries[$number_day] = array();
            array_push($record_entries[$number_day], $record_entry);
          }
        }
        $remove_link_row = manatime_feature_timesheet_make_link_remove_row($this->node, $task->nid);
        $this->addRecord($project->title, $project->nid, $task->title, $task->nid, $record_entries, $total_hours_worked, $remove_link_row);
      }
    }
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
  public function addRecord($project, $project_id, $task, $task_id, $time_entries, $total_hours_worked, $remove_link_row) {
    $this->records[] = array(
      'project_id' => check_plain($project_id),
      'project' => check_plain($project),
      'task_id' => check_plain($task_id),
      'task' => check_plain($task),
      'time_entries' => $time_entries,
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
