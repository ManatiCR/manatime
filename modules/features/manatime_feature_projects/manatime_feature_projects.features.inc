<?php
/**
 * @file
 * manatime_feature_projects.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function manatime_feature_projects_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function manatime_feature_projects_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function manatime_feature_projects_node_info() {
  $items = array(
    'projects' => array(
      'name' => t('Projects'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
