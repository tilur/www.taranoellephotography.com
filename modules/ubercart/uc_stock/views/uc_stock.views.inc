<?php
// $Id: uc_stock.views.inc,v 1.5 2010/07/15 20:32:40 islandusurper Exp $

/**
 * @file
 * Views 2 hooks and callback registries.
 */

/**
 * Implement hook_views_data().
 */
function uc_stock_views_data() {
  $data['uc_product_stock']['table']['group'] = t('Stock');

  $data['uc_product_stock']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  $data['uc_product_stock']['sku'] = array(
    'title' => t('SKU'),
    'help' => t('The model or SKU of the stock level'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['uc_product_stock']['active'] = array(
    'title' => t('Active'),
    'help' => t('Whether or not the stock level is currently being tracked'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Active'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['uc_product_stock']['stock'] = array(
    'title' => t('Stock Level'),
    'help' => t('The current stock level'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['uc_product_stock']['threshold'] = array(
    'title' => t('Threshold'),
    'help' => t('The threshold or warning limit of the stock level'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['uc_product_stock']['below_threshold'] = array(
    'title' => t('Is Below Threshold'),
    'help' => t('Filter the node based on whether its stock level is below the threshold for the SKU.'),
    'filter' => array(
      'handler' => 'uc_stock_views_handler_filter_below_threshold',
      'label' => t('Is Below Threshold'),
      'type' => 'yes-no',
    ),
  );

  return $data;
}

/**
 * Implement hook_views_handlers().
 */
function uc_stock_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'uc_stock') . '/views',
    ),
    'handlers' => array(
      'uc_stock_views_handler_filter_below_threshold' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
    ),
  );
}
