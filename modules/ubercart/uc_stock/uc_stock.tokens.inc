<?php
// $Id: uc_stock.tokens.inc,v 1.1 2010/04/07 20:44:27 islandusurper Exp $

/**
 * @file
 * Token hooks.
 */

/**
 * Implement hook_token_info().
 */
function uc_stock_token_info() {
  $type = array(
    'name' => t('Stock level'),
    'description' => t('Tokens for the stock levels of products.'),
    'needs-data' => 'uc_stock',
  );

  $stock['level'] = array(
    'name' => t('Level'),
    'description' => t('The current stock level'),
  );
  $stock['model'] = array(
    'name' => t('Model'),
    'description' => t('The model or SKU of the stock level'),
  );
  $stock['threshold'] = array(
    'name' => t('Threshold'),
    'description' => t('The threshold or warning limit of the stock level'),
  );

  return array(
    'types' => array('uc_stock' => $type),
    'tokens' => array('uc_stock' => $stock),
  );
}

/**
 * Implement hook_tokens().
 */
function uc_stock_tokens($type, $tokens, $data = array(), $options = array()) {
  $values = array();

  if ($type == 'uc_stock' && !empty($data['uc_stock'])) {
    $object = $data['uc_stock'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'level':
          $values[$original] = $object->stock;
          break;

        case 'model':
          $values[$original] = $object->sku;
          break;

        case 'threshold':
          $values[$original] = $object->threshold;
          break;
      }
    }
  }

  return $values;
}

