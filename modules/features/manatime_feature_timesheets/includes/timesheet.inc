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
   */
  public function getNid() {
    return $this->node->nid;
  }

  /**
   * Set status.
   */
  public function setStatus($status) {
    $this->status = $status;
  }

  /**
   * Get status.
   */
  public function getStatus() {
    return $this->status;
  }

  /**
   * Get uid.
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
   * Get time_entries.
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
   * Get projects.
   */
  public function getProjects() {
    return $this->projects;
  }

  /**
   * Get time_entries per day.
   */
  public function getTimeEntriesPerDay($day) {
    $entries = array();
    foreach ($this->timeEntries as $entry) {
      if ($entry->field_date[LANGUAGE_NONE][0]['value'] === $day) {
        $entries[] = $entry;
      }
    }
    return $entries;
  }

  /**
   * Get time_entries per task.
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
   * Returns the reports in an array.
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
        $this->addRecord($project->title, $task->title, $record_entries, $total_hours_worked, $remove_link_row);
      }
    }
  }

  /**
   * Get records.
   */
  public function getRecords() {
    // Report fields: project, task and time entries.
    return $this->records;
  }

  /**
   * Add record.
   */
  public function addRecord($project, $task, $time_entries, $total_hours_worked, $remove_link_row) {
    $this->records[] = array(
      'project' => check_plain($project),
      'task' => check_plain($task),
      'time_entries' => $time_entries,
      'total_hours_worked' => check_plain($total_hours_worked),
      'remove_link_row' => $remove_link_row,
    );
  }

  /**
   * Remove record.
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

}
