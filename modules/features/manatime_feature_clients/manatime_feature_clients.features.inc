<?php
/**
 * @file
 * manatime_feature_clients.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function manatime_feature_clients_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function manatime_feature_clients_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function manatime_feature_clients_node_info() {
  $items = array(
    'clients' => array(
      'name' => t('Clients'),
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
