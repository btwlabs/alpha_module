<?php
/**
 * @file
 * alpha_module.admin.inc
 *
 * Replace alpha_module_entity with the actual entity name.
 */

/**
 * Group delete form.
 */
function alpha_module_entity_form_delete_confirm($form, &$form_state, $key_group) {
  $form_state['alpha_module_entity'] = $key_group;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['alpha_module_entity_id'] = array('#type' => 'value', '#value' => entity_id('alpha_module_entity' ,$key_group));
  return confirm_form($form,
    t('Are you sure you want to delete the group %title?', array('%title' => entity_label('alpha_module_entity', $key_group))),
    'group/' . entity_id('alpha_module_entity' ,$key_group),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Group delete form submit handler.
 */
function alpha_module_entity_form_delete_confirm_submit($form, &$form_state) {
  $alpha_module_entity = $form_state['alpha_module_entity'];
  alpha_module_entity_delete($alpha_module_entity);

  watchdog('alpha_module_entity', '@alpha_module_entity: deleted %title.', array('@alpha_module_entity' => $alpha_module_entity->group, '%title' => $alpha_module_entity->label));
  drupal_set_message(t('@alpha_module_entity %title has been deleted.', array('@alpha_module_entity' => $alpha_module_entity->group, '%title' => $alpha_module_entity->label)));

  $form_state['redirect'] = '<= specify url =>';
}

/**
 * Group Form.
 */
function alpha_module_entity_form($form, &$form_state, $alpha_module_entity = NULL) {
  
}

/**
 * Group submit handler.
 */
function alpha_module_entity_form_submit(&$form, &$form_state) {
  
}

/**
 * Callback for the cancel link on group forms.
 */
function alpha_module_entity_form_cancel() {
  drupal_goto('admin/structure/groups');
}

/**
 * Form to delete a discount.
 * @param array $form
 * @param array $form_state
 * @param stdClass$ck_group
 */
function alpha_module_entity_delete_form($form, &$form_state,$ck_group) {

}

/**
 * Submit callback for deleting a discount.
 * @param array $form
 * @param array $form_state
 */
function alpha_module_entity_delete_form_submit(&$form, &$form_state) {

}