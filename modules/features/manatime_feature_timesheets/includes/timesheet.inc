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
  private $user;
  private $timeEntries;
  private $projects = array();
  private $status;
  private $records;

  /**
   * Construct.
   */
  public function __construct($nid) {
    $this->node = node_load($nid);
    $this->user = $this->node->uid;
    $this->status = $this->node->status;
    $this->records = array();

    $this->setTimeEntries();
    $this->setProjects();
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
   * Get status.
   */
  public function getUser() {
    return $this->user;
  }

  /**
   * Get size.
   */
  public function getNumTimeEntries() {
    return count($this->node->field_time_entries[LANGUAGE_NONE]);
  }

  /**
   * Set time_entries.
   */
  public function setTimeEntries() {
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
  public function setProjects() {
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
    $nids = array();
    foreach ($this->timeEntries as $entry) {
      if ($entry->field_date[LANGUAGE_NONE][0]['value'] === $day) {
        $nids[] = $nid;
      }
    }
    return node_load_multiple($nids);
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
    $result = $node->field_tasks[LANGUAGE_NONE];
    $entries = array();
    foreach ($result as $record) {
      $data = $this->getTimeEntriesPerTask($record['target_id']);
      if (!empty($data)) {
        $entries[$record['target_id']] = $data;
      }
    }
    return $entries;
  }

  /**
   * Returns the reports in an array.
   */
  public function generateRecords() {
    foreach ($this->projects as $project) {
      $time_entries = $this->getTimeEntriesPerProject($project->nid);
      foreach ($time_entries as $data) {
        $nid = array_search($data, $time_entries);
        $task = node_load($nid);
        $entries = array();
        foreach ($data as $time_entry) {
          $entry = array(
            'description' => $time_entry->field_duration['und'][0]['value'] . 'hrs = ' . $time_entry->body['und'][0]['value'],
            'duration' => $time_entry->field_duration['und'][0]['value'],
          );
          $timestamp = strtotime($time_entry->field_date['und'][0]['value']);
          $number_day = date('w', $timestamp);
          if (isset($entries[$number_day])) {
            $entries[$number_day][0]['duration'] += $entry['duration'];
            $entries[$number_day][0]['description'] = $entries[$number_day][0]['description'] . '<br />' . $entry['description'];
          }
          else {
            $entries[$number_day] = array();
            array_push($entries[$number_day], $entry);
          }
        }
        $this->records[] = array(
          'project' => $project->title,
          'task' => $task->title,
          'time_entries' => $entries,
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

}
