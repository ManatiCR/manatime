<?php

// Plugin definition
$plugin = array(
  'title' => t('One row two column'),
  'category' => t('Two colums layout'),
  'icon' => 'onerowtwocols.png',
  'theme' => 'onerowtwocols',
  'css' => 'onerowtwocols.css',
  'regions' => array(
    'left' => t('Left side'),
    'right' => t('Right side'),
  ),
);
