<?php /**
 * Copyright (c) 2011, Robin Appelman <icewind1991@gmail.com>
 * This file is licensed under the Affero General Public License version 3 or later.
 * See the COPYING-README file.

 */
 use OCP\User as user;
?>

<?php
if($_['displayNameChangeSupported']) {
?>
<form id="displaynameform">

</form>
<?php
}
?>

<form id="passwordform" class="section">
	<h2>Cliente de sincronização</h2>
	<div id="passwordchanged">Senha alterada com sucesso</div>
	<div id="passworderror">Erro ao alterar senha, senha e confirmação de senha devem ser iguais! </div>
		</br>Usuário: <Strong><em><?php echo user::getUser()?></em></Strong></br>
		Senha:
	<input type="password" id="pass1" name="oldpassword"
		placeholder="<?php echo 'Senha'; ?>"
		autocomplete="off" autocapitalize="off" autocorrect="off" />
	<input type="password" id="pass2" name="personal-password"
		placeholder="<?php echo 'Confirmação'?>"
		data-typetoggle="#personal-show"
		autocomplete="off" autocapitalize="off" autocorrect="off" />
	<input type="checkbox" id="personal-show" name="show" /><label for="personal-show"></label>
	<input id="passwordbutton" type="submit" value="<?php echo $l->t('Change password');?>" />
	<br/>
	<div class="strengthify-wrapper"></div>
</form>

<form>
	<fieldset class="personalblock">
		<h2><?php p($l->t('Language'));?></h2>
		<select id="languageinput" name="lang" data-placeholder="<?php p($l->t('Language'));?>">
			<option value="<?php p($_['activelanguage']['code']);?>">
				<?php p($_['activelanguage']['name']);?>
			</option>
			<?php foreach($_['commonlanguages'] as $language):?>
				<option value="<?php p($language['code']);?>">
					<?php p($language['name']);?>
				</option>
			<?php endforeach;?>
			<optgroup label="––––––––––"></optgroup>
			<?php foreach($_['languages'] as $language):?>
				<option value="<?php p($language['code']);?>">
					<?php p($language['name']);?>
				</option>
			<?php endforeach;?>
		</select>
	</fieldset>
</form>