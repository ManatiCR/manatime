<?php
/**
 * @file
 * manatime_feature_timesheets.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function manatime_feature_timesheets_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function manatime_feature_timesheets_node_info() {
  $items = array(
    'timesheet' => array(
      'name' => t('Timesheet'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
