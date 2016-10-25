<?php

/**
 * @file
 * Timesheet daily view navegation.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Timesheet daily view navegation'),
  'content_types' => 'timesheet_daily_view_navegation',
  'description' => t('Navegation for manatime timesheet daily view.'),
  'render callback' => 'timesheet_daily_view_navegation_render',
  'category' => t('Manatime'),
  'required context' => array(
    new ctools_context_required(t('Timesheet'), 'entity:node'),
  ),
);

/**
 * Callback timesheet_daily_view_render.
 */
function timesheet_daily_view_navegation_render($subtype, $conf, $panel_args, $context) {
  if (isset($context[0]->data)) {
    // Build the content type block.
    $node = $context[0]->data;
    $timesheet = new Timesheet($node);
    $markup = theme_item_list(array(
      'items' => $timesheet->getTimesheetDaysLinks(),
      'title' => NULL,
      'type' => 'ul',
      'attributes' => array('class' => 'daily_view_nav'),));
    $block = new stdClass();
    $block->title = '';
    $block->content = array(
      'content' => array(
        '#markup' => $markup,
      ),
    );
    return $block;
  }
}
