<?php

/**
 * @file
 * Demo content type.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('New task button'),
  'content_types' => 'add_task',
  'description' => t('Action to create a new task.'),
  'render callback' => 'add_task_render',
  'category' => t('Manatime'),
  'required context' => array(
    new ctools_context_required(t('Project'), 'entity:node'),
  ),
);

/**
 * Render the custom content type.
 */
function add_task_render($subtype, $conf, $panel_args, $context) {
  // Single variable for required context.
  list($node) = $context;
  if (empty($node)) {
    return;
  }

  // Build the content type block.
  $block = new stdClass();
  $block->title   = '';
  $block->content = array(
    'content' => array(
      '#markup' => l(t('Add task'), 'node/add/tasks', array(
        'query' => array(
          'id_project' => $node->data->nid,
        ),
      )),
    ),
  );

  return $block;
}
