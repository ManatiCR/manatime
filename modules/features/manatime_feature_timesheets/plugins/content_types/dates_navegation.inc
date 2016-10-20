<?php

/**
 * @file
 * Previous timesheet content type.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Dates navigation.'),
  'content_types' => 'dates_navigation',
  'description' => t('Shows the timesheets navigation arrows.'),
  'render callback' => 'dates_navigation_render',
  'category' => t('Manatime'),
  'required context' => array(
    new ctools_context_required(t('User'), 'entity:user'),
    new ctools_context_required(t('Timesheet'), 'entity:node'),
  ),
);

/**
 * Render the custom content type.
 */
function dates_navigation_render($subtype, $conf, $panel_args, $context) {
  if (isset($context[1]->data)) {
    $node = $context[1]->data;
    $uid = $context[0]->data->uid;
    $items = array();

    // Generate a link to the previous timesheet.
    $date = $node->field_date[LANGUAGE_NONE][0]['value2'];
    $previous_timesheet = '';
    $query = new EntityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'timesheet')
      ->fieldCondition('field_date', 'value2', $date, '<')
      ->fieldCondition('field_user', 'target_id', $uid, '=')
      ->fieldOrderBy('field_date', 'value2', 'DESC')
      ->execute();
    if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $node = node_load(reset($nids));
      $beginning = new DateTime($node->field_date[LANGUAGE_NONE][0]['value']);
      $end = new DateTime($node->field_date[LANGUAGE_NONE][0]['value2']);
      $previous_timesheet = l(t('Previous'), 'timesheet/' . $beginning->format('Ymd') . '-' . $end->format('Ymd'));
      $items[] = array('data' => $previous_timesheet);
    }

    // Generate a link to the current timesheet.
    $current_timesheet = l(t('Today'), 'timesheet');
    $items[] = array('data' => $current_timesheet);

    // Generate a link to the next timesheet.
    $node = $context[1]->data;
    $uid = $context[0]->data->uid;
    $date = $node->field_date[LANGUAGE_NONE][0]['value'];
    $next_timesheet = '';

    $query = new EntityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'timesheet')
      ->fieldCondition('field_date', 'value', $date, '>')
      ->fieldCondition('field_user', 'target_id', $uid, '=')
      ->fieldOrderBy('field_date', 'value2', 'ASC')
      ->execute();

    if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $node = node_load(reset($nids));
      $beginning = new DateTime($node->field_date[LANGUAGE_NONE][0]['value']);
      $end = new DateTime($node->field_date[LANGUAGE_NONE][0]['value2']);
      $next_timesheet = l(t('Next'), 'timesheet/' . $beginning->format('Ymd') . '-' . $end->format('Ymd'));
      $items[] = array('data' => $next_timesheet);
    }
    $content = theme('item_list', array('items' => $items), NULL, 'ul');

    // Build the content type block.
    $block = new stdClass();
    $block->title = '';
    $block->content = array(
      'content' => array(
        '#markup' => $content,
      ),
    );
    return $block;
  }
}
