<?php
// $Id: uc_product_handler_field_buyitnow.inc,v 1.5 2010/04/14 13:37:56 islandusurper Exp $

/**
 * @file
 * Views handler: Simpler "Add to cart" form as a field.
 */

/**
 * Display the simpler Add to cart form like the catalog.
 */
class uc_product_handler_field_buyitnow extends views_handler_field {
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function element_type() {
    if (isset($this->definition['element type'])) {
      return $this->definition['element type'];
    }
    return 'div';
  }

  function render($values) {
    $product = node_load($values->{$this->aliases['nid']});
    if (uc_product_is_product($product)) {
      $form = drupal_get_form('uc_catalog_buy_it_now_form_' . $values->{$this->aliases['nid']}, $product);
      return drupal_render($form);
    }
  }
}
