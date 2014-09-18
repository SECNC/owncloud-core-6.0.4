<div id="documents-content">
	<ul class="documentslist">
		<li class="progress icon-loading"><div><?php p($l->t('Loading documents...')); ?></div></li>
		<li class="document template" data-id="" style="display:none;">
			<a target="_blank" href=""><label></label></a>
		</li>
	</ul>
</div>
<input type="hidden" id="webodf-unstable" value="<?php p($_['useUnstable']) ?>" />
<input type="hidden" name="allowShareWithLink" id="allowShareWithLink" value="<?php p($_['allowShareWithLink']) ?>" />
