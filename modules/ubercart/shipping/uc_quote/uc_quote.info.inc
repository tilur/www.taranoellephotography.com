<?php
// $Id: uc_quote.info.inc,v 1.2 2010/12/17 14:08:17 islandusurper Exp $

/**
 * @file
 * Entity metadata hooks for uc_quote.module.
 */

/**
 * Implement hook_entity_property_info_alter().
 */
function uc_quote_entity_property_info_alter(&$info) {
  $info['uc_order_product']['properties']['shipping_type'] = array(
    'type' => 'text',
    'label' => t('Shipping type'),
    'getter callback' => 'uc_product_get_shipping_type', // not a typical callback.
  );
}
