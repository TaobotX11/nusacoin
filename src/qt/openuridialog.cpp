// Copyright (c) 2011-2025 The Nusacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/openuridialog.h>
#include <qt/platformstyle.h>
#include <qt/forms/ui_openuridialog.h>

#include <qt/guiutil.h>
#include <QAbstractButton>
#include <QLineEdit>
#include <qt/walletmodel.h>

#include <QUrl>

OpenURIDialog::OpenURIDialog(const PlatformStyle* platformStyle, QWidget* parent) : QDialog(parent, GUIUtil::dialog_flags),
                                                                                    ui(new Ui::OpenURIDialog),
                                                                                    m_platform_style(platformStyle)
{
    ui->setupUi(this);
    ui->uriEdit->setPlaceholderText("nusacoin:");
    ui->pasteButton->setIcon(m_platform_style->SingleColorIcon(":/icons/editpaste"));
    QObject::connect(ui->pasteButton, &QAbstractButton::clicked, ui->uriEdit, &QLineEdit::paste);
}

OpenURIDialog::~OpenURIDialog()
{
    delete ui;
}

QString OpenURIDialog::getURI()
{
    return ui->uriEdit->text();
}

void OpenURIDialog::accept()
{
    SendCoinsRecipient rcp;
    if(GUIUtil::parseNusacoinURI(getURI(), &rcp)){
        /* Only accept value URIs */
        QDialog::accept();
    } else {
        ui->uriEdit->setValid(false);
    }
}

void OpenURIDialog::changeEvent(QEvent* e)
{
    if (e->type() == QEvent::PaletteChange) {
        ui->pasteButton->setIcon(m_platform_style->SingleColorIcon(":/icons/editpaste"));
    }

    QDialog::changeEvent(e);
}
