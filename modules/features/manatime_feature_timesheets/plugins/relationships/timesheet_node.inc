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
  'required context' => array(
    new ctools_context_required(t('User'), 'entity:user'),
    new ctools_context_required(t('String'), 'string'),
  ),
);

/**
 * Return a new context based on an existing context.
 */
function timesheet_node_from_user_context($context, $conf) {
  if (empty($context[0]->data)) {
    return ctools_context_create_empty('entity:node', NULL);
  }

  $uid = $context[0]->data->uid;
  // If the url does not have dates, get the current week's timesheet.
  if (empty($context[1]->data)) {
    $beginning = date('w') == 1 ? new DateTime('now') : new DateTime('last monday');
    /*
     * $end = $beginning->getTimestamp()(Monday's number of seconds)
     * + 576000(seven days in seconds).
     */
    $end = $beginning->getTimestamp() + 576000;
    $dates = array($beginning->format('Y-m-d'), gmdate('Y-m-d', $end));
    return manatime_get_timesheet(0, $dates, $dates, 'BETWEEN', $uid);
  }

  else {
    // Get the timesheets with dates given.
    $dates = explode("-", $context[1]->data);
    if (DateTime::createFromFormat('Ymd', $dates[0])
      && DateTime::createFromFormat('Ymd', $dates[1])) {
      $beginning = (new DateTime($dates[0]))->format('Y-m-d');
      $end = (new DateTime($dates[1]))->format('Y-m-d');
      return manatime_get_timesheet(array(1, 0), $beginning, $end, '=', $uid);
    }
    else {
      return ctools_context_create_empty('entity:node', NULL);
    }
  }
}

/**
 * Empty form on purpose.
 */
function timesheet_node_from_user_settings_form($form, $form_state) {
  $conf = $form_state['conf'];
  return $form;
}

/**
 * Get timesheet.
 *
 * @param string $status
 *   The Timesheet's status, possible values: 0 or array(0, 1).
 * @param string $beginning
 *   Beginning date, possible values: date or array(dates).
 * @param string $end
 *   End date, possible values: date or array(dates).
 * @param string $condition
 *   Condition to compare, possible values: '=' or 'BETWEEN'.
 * @param string $uid
 *   The timesheet user's id owner.
 *
 * @return node
 *   If the function found a sheet it return it,
 *   otherwise it return a null node.
 */
function manatime_get_timesheet($status, $beginning, $end, $condition, $uid) {
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'timesheet')
    ->propertyCondition('status', $status)
    ->fieldCondition('field_date', 'value', $beginning, $condition)
    ->fieldCondition('field_date', 'value2', $end, $condition)
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
