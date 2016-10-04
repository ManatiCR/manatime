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
  public function __construct($nid) {
    $this->node = node_load($nid);
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
  public function getNode() {
    return $this->node;
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
    $nids = array();
    foreach ($this->timeEntries as $entry) {
      $nid = $entry->field_project[LANGUAGE_NONE][0]['target_id'];
      if (!in_array($nid, $nids)) {
        $nids[] = $nid;
      }
    }
    $this->projects = node_load_multiple($nids);
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
        $this->records[] = array(
          'project' => check_plain($project->title),
          'task' => check_plain($task->title),
          'task_id' => check_plain($task->nid),
          'time_entries' => $record_entries,
          'total_hours_worked' => $total_hours_worked,
        );
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
  public function addRecord($project, $task) {
    $this->records[] = array(
      'project' => $project,
      'task' => $task,
      'time_entries' => array(),
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
