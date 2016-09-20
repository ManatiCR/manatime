<?php

/**
 * @file
 * Demo content type.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Timesheet view.'),
  'content_types' => 'timesheet_view',
  'description' => t('Template of the Manatime timesheet.'),
  'render callback' => 'timesheet_view_render',
  'category' => t('Manatime'),
  'required context' => array(
    new ctools_context_required(t('Timesheet'), 'entity:node'),
  ),
);

/**
 * Render the custom content type.
 */
function timesheet_view_render($subtype, $conf, $panel_args, $context) {
  if (isset($context[0]->data)) {
    $uid = $context[0]->data->uid;
    // Build the content type block.
    $block = new stdClass();
    $block->title = '';
    $result = $context[0]->data->field_time_entries[LANGUAGE_NONE];
    // Getting the time nids_entries.
    $nids_entries = array();
    foreach ($result as $record) {
      $nids_entries[] = $record['target_id'];
    }
    // Getting the time nids_tasks.
    $nids_tasks = array();
    $entries = node_load_multiple($nids_entries);
    foreach ($entries as $entry) {
      $nid = $entry->field_task[LANGUAGE_NONE][0]['target_id'];
      if (!in_array($nid, $nids_tasks)) {
        $nids_tasks[] = $nid;
      }
    }
    $records = get_timesheet_records($nids_tasks, $uid);
    $block->content = array(
      'content' => array(
        '#theme' => 'timesheet-view',
        '#records' => $records,
      ),
    );
    return $block;
  }
}

/**
 * Return the entries of the timesheet.
 */
function get_timesheet_records($nids_tasks, $uid) {
  $records = array();
  if (isset($nids_tasks)) {
    foreach ($nids_tasks as $nid_task) {
      // Getting the task.
      $task = node_load($nid_task);
      // Getting the project.
      $query = new EntityFieldQuery();
      $result = $query
        ->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'projects')
        ->propertyCondition('status', 1)
        ->fieldCondition('field_tasks', 'target_id', $nid_task, '=')
        ->execute();
      if (isset($result['node'])) {
        $nids = array_keys($result['node']);
        $project = node_load(reset($nids));
      }
      // Getting the time entries.
      $query = new EntityFieldQuery();
      $result = $query
        ->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'time_entries')
        ->propertyCondition('status', 1)
        ->fieldCondition('field_task', 'target_id', $nid_task, '=')
        ->execute();
      if (isset($result['node'])) {
        $nids = array_keys($result['node']);
        $nodes = node_load_multiple($nids);
        $entries = array();
        foreach ($nodes as $node) {
          $date = $node->field_date[LANGUAGE_NONE][0]['value'];
          $timestamp = strtotime($date);
          $number_day = date('w', $timestamp);
          $entry = array(
            'duration' => $node->field_duration[LANGUAGE_NONE][0]['value'],
            'description' => $node->body[LANGUAGE_NONE][0]['value'],
          );
          if (isset($entries[$number_day])) {
            $entries[$number_day][0]['duration'] += $entry['duration'];
            $entries[$number_day][0]['description'] = $entries[$number_day][0]['description'] . ' ' . $entry['description'];
          }
          else {
            $entries[$number_day] = array();
            array_push($entries[$number_day], $entry);
          }
        }
      }
      // Creating new record.
      $record = array(
        'project' => $project->title,
        'task' => $task->title,
        'entries' => $entries,
      );
      $records[] = $record;
    }
  }
  return $records;
}
