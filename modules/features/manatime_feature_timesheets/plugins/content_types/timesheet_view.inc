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
    // Get the records of this timesheet.
    $node = $context[0]->data;
    $timesheet = new Timesheet($node);
    $timesheet->generateRecords();
    $table_headers = array_keys($timesheet->getTimesheetDays());
    array_unshift($table_headers, t('Description'));
    array_push($table_headers, t('Total'));    $records = $timesheet->getRecords();
    // Build the content type block.
    $block = new stdClass();
    $block->title = '';
    $block->content = array(
      'content' => array(
        '#theme' => 'timesheet-view',
        '#timesheet_id' => $node->nid,
        '#table_headers' => $table_headers,
        '#records' => $records,
        '#add_row_link' => manatime_feature_timesheet_make_link_add_row($node),
      ),
    );
    return $block;
  }
}
