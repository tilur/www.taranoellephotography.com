<?php
// $Id: uc_usps.admin.inc,v 1.9 2011/01/11 14:35:38 islandusurper Exp $

/**
 * @file
 * USPS administration menu items.
 */

/**
 * Configure USPS settings.
 *
 * @ingroup forms
 */
function uc_usps_admin_settings($form, &$form_state) {
  $form['uc_usps_user_id'] = array(
    '#type' => 'textfield',
    '#title' => t('USPS user ID'),
    '#description' => t('To acquire or locate your user ID, refer to the <a href="!url">USPS documentation</a>.', array('!url' => 'http://www.ubercart.org/docs/user/312/usps_web_tool_shipping_quote_settings')),
    '#default_value' => variable_get('uc_usps_user_id', ''),
  );

  $form['domestic'] = array(
    '#type' => 'fieldset',
    '#title' => t('USPS Domestic'),
    '#description' => t('Set the conditions that will return a USPS quote.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['domestic']['uc_usps_online_rates'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display USPS "online" rates'),
    '#default_value' => variable_get('uc_usps_online_rates', FALSE),
    '#description' => t('Show your customer standard USPS rates (default) or discounted "online" rates.  Online rates apply only if you, the merchant, pay for and print out postage from the USPS <a href="https://sss-web.usps.com/cns/landing.do">Click-N-Ship</a> web site.'),
  );

  $form['domestic']['uc_usps_env_services'] = array(
    '#type' => 'checkboxes',
    '#title' => t('USPS envelope services'),
    '#default_value' => variable_get('uc_usps_env_services', array_keys(_uc_usps_env_services())),
    '#options' => _uc_usps_env_services(),
    '#description' => t('Select the USPS services that are available to customers. Be sure to include the services that the Postal Service agrees are available to you.'),
  );

  $form['domestic']['env_conditions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Envelope service conditions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $conditions = rules_config_load('get_quote_from_usps_env');
  if ($conditions) {
    $conditions->form($form['domestic']['env_conditions'], $form_state);
  }

  $form['domestic']['uc_usps_services'] = array(
    '#type' => 'checkboxes',
    '#title' => t('USPS parcel services'),
    '#default_value' => variable_get('uc_usps_services', array_keys(_uc_usps_services())),
    '#options' => _uc_usps_services(),
    '#description' => t('Select the USPS services that are available to customers. Be sure to include the services that the Postal Service agrees are available to you.'),
  );

  $form['domestic']['parcel_conditions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Parcel service conditions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $conditions = rules_config_load('get_quote_from_usps');
  if ($conditions) {
    $conditions->form($form['domestic']['parcel_conditions'], $form_state);
  }

  $form['international'] = array(
    '#type' => 'fieldset',
    '#title' => t('USPS International'),
    '#description' => t('Set the conditions that will return a USPS International quote.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['international']['uc_usps_intl_env_services'] = array(
    '#type' => 'checkboxes',
    '#title' => t('USPS international envelope services'),
    '#default_value' => variable_get('uc_usps_intl_env_services', array_keys(_uc_usps_intl_env_services())),
    '#options' => _uc_usps_intl_env_services(),
    '#description' => t('Select the USPS services that are available to customers. Be sure to include the services that the Postal Service agrees are available to you.'),
  );

  $form['international']['env_conditions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Envelope service conditions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $conditions = rules_config_load('get_quote_from_usps_intl_env');
  if ($conditions) {
    $conditions->form($form['international']['env_conditions'], $form_state);
  }

  $form['international']['uc_usps_intl_services'] = array(
    '#type' => 'checkboxes',
    '#title' => t('USPS international parcel services'),
    '#default_value' => variable_get('uc_usps_intl_services', array_keys(_uc_usps_intl_services())),
    '#options' => _uc_usps_intl_services(),
    '#description' => t('Select the USPS services that are available to customers. Be sure to include the services that the Postal Service agrees are available to you.'),
  );

  $form['international']['parcel_conditions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Parcel service conditions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $conditions = rules_config_load('get_quote_from_usps_intl');
  if ($conditions) {
    $conditions->form($form['international']['parcel_conditions'], $form_state);
  }

  $form['uc_usps_markup_type'] = array(
    '#type' => 'select',
    '#title' => t('Markup type'),
    '#default_value' => variable_get('uc_usps_markup_type', 'percentage'),
    '#options' => array(
      'percentage' => t('Percentage (%)'),
      'multiplier' => t('Multiplier (×)'),
      'currency' => t('Addition (!currency)', array('!currency' => variable_get('uc_currency_sign', '$'))),
    ),
  );
  $form['uc_usps_markup'] = array(
    '#type' => 'textfield',
    '#title' => t('Shipping rate markup'),
    '#default_value' => variable_get('uc_usps_markup', '0'),
    '#description' => t('Markup shipping rate quote by dollar amount, percentage, or multiplier.'),
  );
  $form['uc_usps_all_in_one'] = array(
    '#type' => 'radios',
    '#title' => t('Product packages'),
    '#default_value' => variable_get('uc_usps_all_in_one', 1),
    '#options' => array(
      0 => t('Each in its own package'),
      1 => t('All in one'),
    ),
    '#description' => t('Indicate whether each product is quoted as shipping separately or all in one package. Orders with one kind of product will still use the package quantity to determine the number of packages needed, however.'),
  );

  // Taken from system_settings_form(). Only, don't use its submit handler.
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }
  if (!isset($form['#theme'])) {
    $form['#theme'] = 'system_settings_form';
  }

  return $form;
}

/**
 * Validation handler for uc_usps_admin_settings form.
 */
function uc_usps_admin_settings_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['uc_usps_markup'])) {
    form_set_error('uc_usps_markup', t('Rate markup must be a numeric value.'));
  }
}

/**
 * Submit handler for uc_usps_admin_settings form.
 */
function uc_usps_admin_settings_submit($form, &$form_state) {
  $fields = array(
    'uc_usps_user_id',
    'uc_usps_online_rates',
    'uc_usps_env_services',
    'uc_usps_services',
    'uc_usps_intl_env_services',
    'uc_usps_intl_services',
    'uc_usps_markup_type',
    'uc_usps_markup',
    'uc_usps_all_in_once',
  );

  foreach ($fields as $key) {
    $value = $form_state['values'][$key];

    if (is_array($value) && isset($form_state['values']['array_filter'])) {
      $value = array_keys(array_filter($value));
    }
    variable_set($key, $value);
  }

  drupal_set_message(t('The configuration options have been saved.'));

  cache_clear_all();
  drupal_theme_rebuild();
}
