<?php

/**
 * @file
 * Plugin to check whether the url has a validate dates.
 */

$plugin = array(
  'title' => t('Dates access'),
  'description' => t('Returns FALSE if url has invalid dates.'),
  'callback' => 'dates_access_check',
  'summary' => 'dates_access_summary',
  'required context' => array(
    new ctools_context_required(t('String'), 'string'),
  ),
);

/**
 * Check for access.
 */
function dates_access_check($conf, $context) {
  // Return FALSE if the url does not have dates.
  if (empty($context[0]->data)) {
    return FALSE;
  }
  $dates = explode("-", $context[0]->data);
  if (validate_date_format($dates[0]) && validate_date_format($dates[1])) {
    $beginning = new DateTime($dates[0]);
    $end = new DateTime($dates[1]);
    $query = new EntityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'timesheet')
      ->fieldCondition('field_date', 'value', $beginning->format('Y-m-d'), '=')
      ->fieldCondition('field_date', 'value2', $end->format('Y-m-d'), '=')
      ->execute();
    // Return FALSE if there are timesheets with dates given.
    if (isset($result['node'])) {
      return FALSE;
    }
  }
  return TRUE;
}

/**
 * Provides a plugin summary.
 */
function dates_access_summary($conf, $context) {
  return t('Show only if the url has a validate dates');
}
