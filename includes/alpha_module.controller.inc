<?php
/**
 * @file alpha_module.controller.inc
 * Entity Controller.
 */

class CampaignController extends EntityAPIController {
  public function create(array $values = array()) {
    global $user;
    $values += array(
      'alpha_module_entity_id' => '',
    );
    return parent::create($values);
  }
  public function save($entity) {
    parent::save($entity);
    return $this;
  }
  public function delete($ids) {
    $entities = entity_load('alpha_module_entity', $ids);
    foreach($entities as $entity) {
      // Delete Component Entities.
      foreach($entity->data['plugin_data']['entities'] as $type => $attached_entities) {
        foreach($attached_entities as $attached_entity) {
          $id = entity_id($type, $attached_entity);
          entity_delete($type, $id);
        }
      }
      parent::delete(array($entity->alpha_module_entity_id));
    }
  }
}

/**
 * UI controller.
 */
class AlphaModuleController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = t('Manage Alpha Module Entities');
    $items[$this->path]['title'] = t('Alpha Module Entities');
    // Set the add path to use the list function.
    $items[$this->path . '/add']['page callback'] = 'alpha_module_entity_type_table';
    $items[$this->path . '/add']['access callback'] = 'user_access';
    $items[$this->path . '/add']['access arguments'] = array('administer alpha module entities');
    // Pass add links through to a form factory.
    $types = alpha_module_entity_types();
    foreach ($types as $type => $info) {
      $items[$this->path . '/add/' . $type] = array(
        'title' => 'Add ' . $type . '  - Alpha Module Entity',
        'page callback' => 'alpha_module_forms_wrapper',
        'page arguments' => array($type, NULL, 'add'),
        'access callback' => 'entity_access',
        'access arguments' => array('create', 'alpha_module_entity', $type),
        'file' => 'includes/alpha_module.admin.inc',
        'file path' => drupal_get_path('module', 'alpha_module'),
      );
    }
    // Pass manage (edit) calls through to the form factory.
    $items[$this->path . '/manage/%alpha_module_entity']['page callback'] = 'alpha_module_forms_wrapper';
    $items[$this->path . '/manage/%alpha_module_entity']['page arguments'] = array(NULL, 4, 'edit');
    $items[$this->path . '/manage/%alpha_module_entity']['file path'] = drupal_get_path('module', 'alpha_module');
    $items[$this->path . '/manage/%alpha_module_entity']['file'] = 'includes/alpha_module.admin.inc';
    return $items;
  }
}

/**
 *  Entity class.
 */
class AlphaModuleEntity extends Entity {

  public function __construct($values = array()) {
    parent::__construct($values, 'alpha_module_entity');
  }
  protected function defaultLabel() {
    return $this->title;
  }
  protected function defaultUri() {
    return array('path' => 'alpha-module-entities/' . $this->identifier());
  }
  // Return whether alpha module entity is active.
  public function isActive() {
    return $this->active;
  }
  // Activate the alpha module entity.
  public function activate() {
    $this->active = 1;
    $this->save();
  }

}

/**
 *  Campaigns Type class.
 */
class AlphaModuleEntityType extends Entity {
  public $type;
  public $label;
  public $weight = 0;
  public $class = 'AlphaModuleEntityDefault';

  public function __construct($values = array()) {
    parent::__construct($values, 'alpha_module_entity_type');
  }

  protected function defaultLabel() {
    return $this->title;
  }
  protected function defaultUri() {
    return array('path' => 'admin/structure/alpha-module-entities/types/' . $this->identifier());
  }
}

/**
 * UI controller for Types.
 */
class AlphaModuleEntityTypeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = t('Manage Alpha Module Entity Types');
    $items[$this->path]['title'] = t('Alpha Module Entity Types');
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    return $items;
  }
}

/**
 *  Type Controller.
 */
class AlphaModuleEntityTypeController extends EntityAPIController {
  public function create(array $values = array()) {
    $values += array(
      'type' => '',
      'label' => '',
      'description' => '',
      'class' => 'AlphaModuleEntityDefault',
    );
    return parent::create($values);
  }
}
