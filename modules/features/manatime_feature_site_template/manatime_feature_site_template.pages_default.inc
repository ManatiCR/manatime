<?php
/**
 * @file
 * manatime_feature_site_template.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function manatime_feature_site_template_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'site_template__panel_context_5d41e49c-4d30-40d5-8180-2f68aac345d1';
  $handler->task = 'site_template';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Site Template',
    'no_blocks' => 1,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
  );
  $display = new panels_display();
  $display->layout = 'sample_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'first' => NULL,
      'second' => NULL,
      'third' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'd04c864f-5a53-4e73-9559-075e97903543';
  $display->storage_type = 'unknown';
  $display->storage_id = '';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-7154f5b2-4268-410e-97f3-0598af62ac26';
  $pane->panel = 'first';
  $pane->type = 'block';
  $pane->subtype = 'system-main-menu';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 0,
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
  $pane->uuid = '7154f5b2-4268-410e-97f3-0598af62ac26';
  $display->content['new-7154f5b2-4268-410e-97f3-0598af62ac26'] = $pane;
  $display->panels['first'][0] = 'new-7154f5b2-4268-410e-97f3-0598af62ac26';
  $pane = new stdClass();
  $pane->pid = 'new-5b7a8c71-dd77-4bf4-9652-83055ca3aa6f';
  $pane->panel = 'first';
  $pane->type = 'pane_messages';
  $pane->subtype = 'pane_messages';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '5b7a8c71-dd77-4bf4-9652-83055ca3aa6f';
  $display->content['new-5b7a8c71-dd77-4bf4-9652-83055ca3aa6f'] = $pane;
  $display->panels['first'][1] = 'new-5b7a8c71-dd77-4bf4-9652-83055ca3aa6f';
  $pane = new stdClass();
  $pane->pid = 'new-647a9e16-3d3d-4219-ac59-63463ac960c6';
  $pane->panel = 'second';
  $pane->type = 'page_content';
  $pane->subtype = 'page_content';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'context' => 'argument_page_content_1',
    'override_title' => 0,
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
  $pane->uuid = '647a9e16-3d3d-4219-ac59-63463ac960c6';
  $display->content['new-647a9e16-3d3d-4219-ac59-63463ac960c6'] = $pane;
  $display->panels['second'][0] = 'new-647a9e16-3d3d-4219-ac59-63463ac960c6';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-7154f5b2-4268-410e-97f3-0598af62ac26';
  $handler->conf['display'] = $display;
  $export['site_template__panel_context_5d41e49c-4d30-40d5-8180-2f68aac345d1'] = $handler;

  return $export;
}
