<?php
// $Id: uc_payment.rules.inc,v 1.2 2010/08/25 13:40:25 islandusurper Exp $

/**
 * @file
 * Rules definitions.
 */

/**
 * Implement hook_rules_event_info().
 */
function uc_payment_rules_event_info() {
  $events['uc_payment_entered'] = array(
    'label' => t('A payment gets entered for an order'),
    'group' => t('Payment'),
    'variables' => array(
      'order' => array(
        'type' => 'uc_order',
        'label' => t('Order'),
      ),
      'account' => array(
        'type' => 'user',
        'label' => t('User'),
      ),
    ),
  );

  return $events;
}

/**
 * Implement hook_rules_condition_info().
 */
function uc_payment_rules_condition_info() {
  $conditions['uc_payment_condition_order_balance'] = array(
    'label' => t('Check the order balance'),
    'group' => t('Payment'),
    'base' => 'uc_payment_condition_order_balance',
    'parameter' => array(
      'order' => array(
        'type' => 'uc_order',
        'label' => t('Order'),
        'restriction' => 'selector',
      ),
      'balance_comparison' => array(
        'type' => 'text',
        'label' => t('Operator'),
        'options list' => 'uc_payment_condition_balance_options',
        'restriction' => 'input',
      ),
    ),
  );

  return $conditions;
}

/**
 * Condition: Check the current order balance.
 */
function uc_payment_condition_order_balance($order, $balance_comparison) {
  $balance = uc_payment_balance($order);

  switch ($balance_comparison) {
    case 'less':
      return $balance < 0;
    case 'less_equal':
      return $balance <= 0.01;
    case 'equal':
      return $balance < 0.01 && $balance > -0.01;
    case 'greater':
      return $balance >= 0.01;
  }
}

function uc_payment_condition_balance_options() {
  $zero = array('!zero' => uc_currency_format(0));
  $options = array(
    'less' => t('Balance is less than !zero.', $zero),
    'less_equal' => t('Balance is less than or equal to !zero.', $zero),
    'equal' => t('Balance is equal to !zero.', $zero),
    'greater' => t('Balance is greater than !zero.', $zero),
  );

  return $options;
}

