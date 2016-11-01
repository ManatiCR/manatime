<?php
/**
 * @file
 * Plugin to check whether the url has a validate dates.
 */

$plugin = array(
  'title' => t('Day access'),
  'description' => t('Returns FALSE if the url has invalid day.'),
  'callback' => 'day_access_check',
  'summary' => 'day_access_summary',
  'required context' => array(
    new ctools_context_required(t('String'), 'string'),
    new ctools_context_required(t('Timesheet'), 'entity:node'),
  ),
);

/**
 * Check for access.
 */
function day_access_check($conf, $context) {
  // Return FALSE if the url does not have dates.
  if (empty($context[0]->data)) {
    return FALSE;
  }
  $day = $context[0]->data;
  if (DateTime::createFromFormat('Ymd', $day)) {
    $day = date("Y-m-d H:i:s", strtotime($day));
    $node = $context[1]->data;
    $timesheet = new Timesheet($node);
    $days = $timesheet->getTimesheetDays();
    foreach ($days as $existing_day) {
      if ($existing_day === $day) {
        return FALSE;
      }
    }
  }
  return TRUE;
}

/**
 * Provides a plugin summary.
 */
function day_access_summary($conf, $context) {
  return t('Show only if the url has a validate dates');
}
