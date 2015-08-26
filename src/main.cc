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


#include <qwidget.h>
#include <iostream>
#include "globals.h"
#include "utils.h"


/* Globals */
QCommandLineParser *parser;
MainWindow         *window;
OSHandling         *osh;
SubDownloader      *downh;

int main(int ac, char **argv)
{
    QApplication* app = new QApplication(ac, argv);
    app->setApplicationName("QSubber");
    app->setApplicationVersion(QSUBBER_VERSION);

    parser = new QCommandLineParser;
    parser->addHelpOption();
    parser->addVersionOption();
    parser->addPositionalArgument("media", "Media file to search subtitle for.");
    parser->process(*app);

    settings = Settings::loadSettings();

    osh = new OSHandling;
    osh->fetchSubLanguages();

    downh = new SubDownloader;

    window = new MainWindow;
    window->show();

    osh->LogIn("", "");

    int ret = app->exec();

    delete window;
    delete osh;
    delete downh;
    delete settings;
    delete parser;
    delete app;

    return ret;
}
