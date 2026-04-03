<?php
/**
 * @file
 * Provide views data.
 */

/**
 * Implements hook_views_data().
 */
function entity_modified_views_data() {
  $data = array();

  // The 'group' index will be used as a prefix in the UI for any of this
  // table's fields, sort criteria, etc. so it's easy to tell where they came
  // from.
  $data['entity_modified']['table']['group'] = t('Entity modified');

  $data['entity_modified']['modified'] = array(
    'title' => t('Date updated'),
    'help' => t('The date this entity was modified last.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function entity_modified_views_data_alter(&$data) {
  // Inject our own field if it's not a property of the entity itself.
  foreach (entity_get_info() as $entity_type => $entity_info) {
    if (isset($entity_info['base table']) && isset($data[$entity_info['base table']]) && !entity_modified_property_name($entity_type)) {
      $data[$entity_info['base table']]['entity_modified'] = array(
        'title' => t('Date updated'),
        'help' => t('The date this entity was last modified.'),
        'relationship' => array(
          'label' => t('Entity Modified'),
          'title' => t('Entity Modified'),
          'base' => 'entity_modified',
          'base field' => 'entity_id',
          // The entity specific properties to use for the join query.
          'field' => $entity_info['entity keys']['id'],
          'handler' => 'views_handler_relationship',
          'extra' => array(
            array('field' => 'entity_type', 'value' => $entity_type),
          ),
        ),
      );
    }
  }
}
