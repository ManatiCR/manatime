<?php
/**
 * @file
 * manatime_feature_time_entries.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function manatime_feature_time_entries_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function manatime_feature_time_entries_node_info() {
  $items = array(
    'time_entries' => array(
      'name' => t('Time entries'),
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
