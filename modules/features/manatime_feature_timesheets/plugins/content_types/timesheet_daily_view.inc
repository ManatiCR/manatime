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
  ),
);

/**
 * Callback timesheet_daily_view_render.
 */
function timesheet_daily_view_render($subtype, $conf, $panel_args, $context) {
  // Build the content type block.
  $node = $context[0]->data;
  $timesheet = new Timesheet($node);
  $current_date = (new DateTime('now 00:00'))->format('Y-m-d H:i:s');
  $current_entries = $timesheet->getTimeEntriesPerDay($current_date);
  $time_entries = $timesheet->getTimeEntriesArray($current_entries);
  $test = $timesheet->getDateLinks();
  $block = new stdClass();
  $block->title = '';
  $block->content = array(
    'content' => array(
      '#theme' => 'timesheet-daily-view',
      '#time_entries' => $time_entries,
      '#test' => $test,
    ),
  );
  return $block;
}
