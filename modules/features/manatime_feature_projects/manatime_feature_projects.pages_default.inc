<?php
/**
 * @file
 * manatime_feature_projects.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function manatime_feature_projects_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_021763f9-9425-45b7-951f-acb6b5b39ada';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Project Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'projects' => 'projects',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'f9cfa5f8-7d4e-4b83-8764-d9595d1a9dbd';
  $display->storage_type = 'unknown';
  $display->storage_id = '';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-16f85efd-e42e-4411-abaf-8e36c18bd7ad';
  $pane->panel = 'middle';
  $pane->type = 'node_title';
  $pane->subtype = 'node_title';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'link' => 0,
    'markup' => 'none',
    'id' => '',
    'class' => '',
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '16f85efd-e42e-4411-abaf-8e36c18bd7ad';
  $display->content['new-16f85efd-e42e-4411-abaf-8e36c18bd7ad'] = $pane;
  $display->panels['middle'][0] = 'new-16f85efd-e42e-4411-abaf-8e36c18bd7ad';
  $pane = new stdClass();
  $pane->pid = 'new-da5cda26-ecf8-44cd-bc66-9179dd2fbf11';
  $pane->panel = 'middle';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_client';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'entityreference_label',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'link' => 1,
    ),
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => 'Clients',
    'override_title_heading' => 'h3',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'da5cda26-ecf8-44cd-bc66-9179dd2fbf11';
  $display->content['new-da5cda26-ecf8-44cd-bc66-9179dd2fbf11'] = $pane;
  $display->panels['middle'][1] = 'new-da5cda26-ecf8-44cd-bc66-9179dd2fbf11';
  $pane = new stdClass();
  $pane->pid = 'new-8d7895f4-8667-4fcc-a896-dd8073d30fa4';
  $pane->panel = 'middle';
  $pane->type = 'node_body';
  $pane->subtype = 'node_body';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '8d7895f4-8667-4fcc-a896-dd8073d30fa4';
  $display->content['new-8d7895f4-8667-4fcc-a896-dd8073d30fa4'] = $pane;
  $display->panels['middle'][2] = 'new-8d7895f4-8667-4fcc-a896-dd8073d30fa4';
  $pane = new stdClass();
  $pane->pid = 'new-de0e0ef3-1be1-419c-9eb5-6f0285d5567d';
  $pane->panel = 'middle';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_active';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'list_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => 'Status',
    'override_title_heading' => 'h3',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = 'de0e0ef3-1be1-419c-9eb5-6f0285d5567d';
  $display->content['new-de0e0ef3-1be1-419c-9eb5-6f0285d5567d'] = $pane;
  $display->panels['middle'][3] = 'new-de0e0ef3-1be1-419c-9eb5-6f0285d5567d';
  $pane = new stdClass();
  $pane->pid = 'new-98c132ca-b5c3-4267-8826-462b0975b03d';
  $pane->panel = 'middle';
  $pane->type = 'views_panes';
  $pane->subtype = 'tasks_listing-panel_pane_1';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'arguments' => array(
      'nid' => '%node:nid',
    ),
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '98c132ca-b5c3-4267-8826-462b0975b03d';
  $display->content['new-98c132ca-b5c3-4267-8826-462b0975b03d'] = $pane;
  $display->panels['middle'][4] = 'new-98c132ca-b5c3-4267-8826-462b0975b03d';
  $pane = new stdClass();
  $pane->pid = 'new-c2f3d09a-5dd7-4668-8352-be3a48703bcd';
  $pane->panel = 'middle';
  $pane->type = 'add_task';
  $pane->subtype = 'add_task';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = 'c2f3d09a-5dd7-4668-8352-be3a48703bcd';
  $display->content['new-c2f3d09a-5dd7-4668-8352-be3a48703bcd'] = $pane;
  $display->panels['middle'][5] = 'new-c2f3d09a-5dd7-4668-8352-be3a48703bcd';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-16f85efd-e42e-4411-abaf-8e36c18bd7ad';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_021763f9-9425-45b7-951f-acb6b5b39ada'] = $handler;

  return $export;
}
