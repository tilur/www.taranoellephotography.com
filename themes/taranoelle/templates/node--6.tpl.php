<?php
  $node = node_load($nid);

  $main_menu_tree = menu_tree_all_data('main-menu');
  $galleries = array_shift($main_menu_tree);
  $galleries = $galleries['below'];

?>
  <div id="node-10" class="content-wrapper node node-page node-full clearfix">
    <h2><?php print $node->title; ?></h2>

    <div class="content clearfix">
      <div class="field field-name-body field-type-text-with-summary field-label-hidden">
<?php
  foreach ($galleries AS $gallery => $data) {
    print $data['link']['link_title'].'<br>';

      foreach ($data['below'] AS $subgallery => $subdata) {
	print '&nbsp;&nbsp;&nbsp;<a href="'.drupal_get_path_alias($subdata['link']['link_path']).'">'.$subdata['link']['link_title'].'</a><br>';
      }
  }
?>
      </div>
    </div>
  </div>
