<?php

/**
 * @file
 * Previous timesheet content type.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Previous timesheet.'),
  'content_types' => 'previous_timesheet',
  'description' => t('Shows the navigation arrow to the previous timesheet.'),
  'render callback' => 'previous_timesheet_render',
  'category' => t('Manatime'),
  'required context' => array(
    new ctools_context_required(t('User'), 'entity:user'),
    new ctools_context_required(t('Timesheet'), 'entity:node'),
  ),
);

/**
 * Render the custom content type.
 */
function previous_timesheet_render($subtype, $conf, $panel_args, $context) {
  if (isset($context[1]->data)) {
    $node = $context[1]->data;
    $uid = $context[0]->data->uid;
    $date = $node->field_date[LANGUAGE_NONE][0]['value'];
    $previous_link = '';

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
      $previous_link = l(t('Previous'), 'timesheet/' . $beginning->format('Ymd') . '-' . $end->format('Ymd'));
    }

    // Build the content type block.
    $block = new stdClass();
    $block->title = '';
    $block->content = array(
      'content' => array(
        '#markup' => $previous_link,
      ),
    );
    return $block;
  }
}
