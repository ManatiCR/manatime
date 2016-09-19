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

  $uid = $context->data->uid;
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'timesheet')
    ->propertyCondition('status', 0)
    ->fieldCondition('field_date', 'value', array('2016-09-12', '2016-09-20'), 'BETWEEN')
    ->fieldCondition('field_user', 'target_id', $uid, '=')
    ->execute();

  if (isset($result['node'])) {
    $nids = array_keys($result['node']);
    $nid = reset($nids);
    $node = node_load($nid);
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
