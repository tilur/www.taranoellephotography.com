<?php
// $Id: uc_catalog.pathauto.inc,v 1.1 2010/11/29 22:18:57 islandusurper Exp $

/**
 * @file
 * Pathauto hooks.
 */

/**
 * Implement hook_pathauto().
 */
function uc_catalog_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'uc_catalog';
      $settings['token_type'] = 'term';
      $settings['groupheader'] = t('Catalog paths');
      $settings['patterndescr'] = t('Pattern for catalog pages');
      $settings['patterndefault'] = 'catalog/[term:name]';
      $settings['supportsfeeds'] = 'feed';
      $settings['batch_update_callback'] = 'uc_catalog_pathauto_bulkupdate';
      $settings['batch_file'] = drupal_get_path('module', 'uc_catalog') . '/uc_catalog.pathauto.inc';

    return (object) $settings;
  }
}

/**
 * Implement hook_pathauto_bulkupdate().
 *
 * Generate aliases for all categories without aliases
 */
function uc_catalog_pathauto_bulkupdate(&$context) {
  if (!isset($context['sandbox']['current'])) {
    $context['sandbox']['count'] = 0;
    $context['sandbox']['current'] = 0;
  }

  $catalog_vid = variable_get('uc_catalog_vid', 0);
  $query = db_select('taxonomy_term_data', 'td');
  $concat = _pathauto_sql_concat("'catalog/'", 'td.tid');
  $query->leftJoin('url_alias', 'ua', "$concat = ua.source");
  $query->addField('td', 'tid');
  $query->isNull('ua.source');
  $query->condition('vid', $catalog_vid);
  $query->orderBy('td.tid');
  $query->addTag('pathauto_bulk_update');
  $query->addMetaData('entity', 'taxonomy_term');

  // Get the total amount of items to process.
  if (!isset($context['sandbox']['total'])) {
    $context['sandbox']['total'] = $query->countQuery()->execute()->fetchField();

    // If there are no nodes to update, the stop immediately.
    if (!$context['sandbox']['total']) {
      $context['finished'] = 1;
      return;
    }
  }

  $query->range(0, 25);
  $tids = $query->execute()->fetchCol();
  $terms = taxonomy_term_load_multiple($tids);

  $count = 0;
  $placeholders = array();
  foreach ($terms as $category) {
    $count = _uc_catalog_pathauto_alias($category, 'bulkupdate') + $count;
  }

  $context['sandbox']['count'] += count($tids);
  $context['sandbox']['current'] = max($tids);
  $context['message'] = t('Updated alias for term @tid.', array('@tid' => end($tids)));

  if ($context['sandbox']['count'] != $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
}

/**
 * Create aliases for taxonomy objects
 *
 * @param $category
 *   A taxonomy object
 */
function _uc_catalog_pathauto_alias($category, $op) {
  module_load_include('inc', 'pathauto');
  $count = 0;

  if ($category->vid == variable_get('uc_catalog_vid', 0)) {
    // Check that the term has its bundle, which is the vocabulary's machine name.
    if (!isset($category->vocabulary_machine_name)) {
      $vocabulary = taxonomy_vocabulary_load($term->vid);
      $category->vocabulary_machine_name = $vocabulary->machine_name;
    }

    $src = uc_catalog_path($category);

    if ($alias = pathauto_create_alias('uc_catalog', $op, $src, array('term' => $category), $category->vocabulary_machine_name)) {
      $count++;
    }
  }

  return $count;
}

/**
 * Implement hook_path_alias_types().
 */
function uc_catalog_path_alias_types() {
  return array('catalog/' => t('Catalog pages'));
}
