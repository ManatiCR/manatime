<?php

/**
 * @file
 * Plugin to provide a timesheet node.
 */

/**
 * Description to the array $plugin.
 */
$plugin = array(
  'title' => t('Timesheet node'),
  'description' => t("Load the user timesheet."),
  'keyword' => 'node',
  'context' => 'timesheet_node_from_user_context',
  'edit form' => 'timesheet_node_from_user_settings_form',
  'required context' => new ctools_context_required(t('User'), 'entity:user'),
);

/**
 * Return a new context based on an existing context.
 */
function timesheet_node_from_user_context($context, $conf) {
  if (empty($context->data)) {
    return ctools_context_create_empty('entity:node', NULL);
  }
  if (date('w') == 1) {
    $beginning = new DateTime('now');
  }
  else {
    $beginning = new DateTime('last monday');
  }
  $end = $beginning->getTimestamp() + 576000;
  $uid = $context->data->uid;
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'timesheet')
    ->propertyCondition('status', 0)
    ->fieldCondition('field_date', 'value', array(
      $beginning->format('Y-m-d'),
      gmdate('Y-m-d', $end),
    ), 'BETWEEN')
    ->fieldCondition('field_user', 'target_id', $uid, '=')
    ->execute();

  if (isset($result['node'])) {
    $nids = array_keys($result['node']);
    $node = node_load(reset($nids));
    return ctools_context_create('entity:node', $node);
  }
  else {
    return ctools_context_create_empty('entity:node', NULL);
  }

}

/**
 * Empty form on purpose.
 */
function timesheet_node_from_user_settings_form($form, $form_state) {
  $conf = $form_state['conf'];
  return $form;
}
