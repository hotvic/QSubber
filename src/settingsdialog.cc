/*
 * This file is part of QSubber.
 *
 * QSubber is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QSubber is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QSubber.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "settingsdialog.hh"

namespace QSubber
{
SettingsDialog::SettingsDialog()
{
  Application* app = static_cast<Application*>(qApp);

  this->ui.setupUi(this);

  this->ui.lblLoginStatus->hide();

  /* Load values */
  ui.userEdit->setText(app->settings->getConfig("auth_user"));
  ui.passEdit->setText(app->settings->getConfig("auth_pass"));

  this->auth_user_changed();
  this->auth_pass_changed();

  this->updateLoginButtonState();

  /* Signals / Slots */
  connect(this, &QDialog::accepted, this, &SettingsDialog::accepted);
  connect(&(app->osh), &OSHandling::loginResult, this, &SettingsDialog::onLogin);
  connect(ui.userEdit, &QLineEdit::textChanged, this, &SettingsDialog::auth_user_changed);
  connect(ui.passEdit, &QLineEdit::textChanged, this, &SettingsDialog::auth_pass_changed);
}

void SettingsDialog::accepted()
{
  Application* app = static_cast<Application*>(qApp);

  QHashIterator<QString, QString> i(values);
  while (i.hasNext())
  {
    i.next();
    app->settings->setConfig(i.key(), i.value());
  }
}

void SettingsDialog::auth_user_changed()
{
  values["auth_user"] = ui.userEdit->text();

  this->updateLoginButtonState();
}

void SettingsDialog::auth_pass_changed()
{
  values["auth_pass"] = ui.passEdit->text();

  this->updateLoginButtonState();
}

void SettingsDialog::onLogin(bool successful, QString sid)
{
  if (successful)
  {
    this->ui.lblLoginStatus->setText(tr("Login success! Session ID: ") + sid);
  }
  else
  {
    this->ui.lblLoginStatus->setText(tr("Login Failed..."));
  }
}

void SettingsDialog::on_btnLogin_clicked()
{
  dynamic_cast<Application*>(qApp)->osh.login(values["auth_user"], values["auth_pass"]);

  this->ui.lblLoginStatus->setText(tr("Logging in..."));
  this->ui.lblLoginStatus->show();
}

void SettingsDialog::updateLoginButtonState()
{
  bool enabled = !(this->values["auth_user"].isEmpty() || this->values["auth_pass"].isEmpty());

  this->ui.btnLogin->setEnabled(enabled);
}
}
