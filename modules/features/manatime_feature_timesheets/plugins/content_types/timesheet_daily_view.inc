<?php

/**
 * @file
 * Timesheet daily view.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Timesheet daily view'),
  'content_types' => 'timesheet_daily_view',
  'description' => t('Template for manatime timesheet daily view.'),
  'render callback' => 'timesheet_daily_view_render',
  'category' => t('Manatime'),
  'required context' => array(
    new ctools_context_required(t('Timesheet'), 'entity:node'),
    new ctools_context_required(t('String'), 'string'),
  ),
);

/**
 * Callback timesheet_daily_view_render.
 */
function timesheet_daily_view_render($subtype, $conf, $panel_args, $context) {
  if (isset($context[0]->data)) {
    // Build the content type block.
    $node = $context[0]->data;
    $timesheet = new Timesheet($node);
    if (isset($context[1]->data)) {
      if (DateTime::createFromFormat('Ymd', $context[1]->data)) {
        $day = date('Y-m-d', strtotime($context[1]->data));
        $entries = $timesheet->getTimeEntriesPerDay($day);
      }
    }
    else {
      $current_date = (new DateTime('now'))->format('Y-m-d');
      $entries = $timesheet->getTimeEntriesPerDay($current_date);
    }
    $time_entries = $timesheet->getTimeEntriesArray($entries);
    $table_headers = array(
      'project' => t('Project'),
      'task' => t('Task'),
      'description' => t('Description'),
      'duration' => t('Duration'),
    );
    $block = new stdClass();
    $block->title = '';
    $block->content = array(
      'content' => array(
        '#theme' => 'timesheet-daily-view',
        '#time_entries' => $time_entries,
        '#table_headers' => $table_headers,
      ),
    );
    return $block;
  }
}
