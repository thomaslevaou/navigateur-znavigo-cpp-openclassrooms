#include "FenPrincipale.h"

FenPrincipale::FenPrincipale()
{
  setMinimumSize(500, 350);
  homepageUrlText = QString("https://www.duckduckgo.com/");
  homepageUrl = QUrl(homepageUrlText);
  setWindowTitle("zNavigo, le navigateur web des Zéros");
  m_progressBar = new QProgressBar(this);
  m_labelProgressBar = new QLabel(QString("0%"));
  creerActions();
  creerMenus();
  creerBarreOutils();
  creerZoneCentrale();
  creerStatusBar();
  creerLiensSignauxSlots();
}

void FenPrincipale::creerActions() {
  m_nouvelOnglet = new QAction("Ouvrir un nouvel onglet", this);
  m_nouvelOnglet->setShortcut(QKeySequence("Ctrl+T"));
  m_fermerOnglet = new QAction("Fermer l'onglet actif", this);
  m_fermerOnglet->setShortcut(QKeySequence("Ctrl+W"));
  m_actionQuit = new QAction("&Fermer le navigateur", this);
  m_actionQuit->setShortcut(QKeySequence("Ctrl+Q"));
  m_actionPrecedente = new QAction("Page précédente", this);
  m_actionPrecedente->setIcon(QIcon("znavigo/icons/back.png"));
  m_actionSuivante = new QAction("Page suivante", this);
  m_actionSuivante->setIcon(QIcon("znavigo/icons/next.png"));
  m_actionCancelLoad = new QAction("Arrêter le chargement de la page", this);
  m_actionCancelLoad->setIcon(QIcon("znavigo/icons/close.png"));
  m_actionRefresh= new QAction("Actualiser", this);
  m_actionRefresh->setIcon(QIcon("znavigo/icons/refresh.png"));
  m_actionHome = new QAction("Revenir à la Page d'accueil", this);
  m_actionHome->setIcon(QIcon("znavigo/icons/home.png"));
  m_actionGo = new QAction("Aller sur la page entrée", this);
  m_actionGo->setIcon(QIcon("znavigo/icons/go.png"));
  m_actionGo->setShortcut(QKeySequence("Ctrl+E"));
  m_apropos = new QAction("A propos...", this);
  m_apropos_qt = new QAction("A propos de Qt...", this);
}

void FenPrincipale::creerMenus() {
  QMenu *menuFichier = menuBar()->addMenu("&Fichier");
  menuFichier->addAction(m_nouvelOnglet);
  menuFichier->addAction(m_fermerOnglet);
  menuFichier->addAction(m_actionQuit);
  QMenu *menuNavigation = menuBar()->addMenu("&Navigation");
  menuNavigation->addAction(m_actionPrecedente);
  menuNavigation->addAction(m_actionSuivante);
  menuNavigation->addAction(m_actionCancelLoad);
  menuNavigation->addAction(m_actionRefresh);
  menuNavigation->addAction(m_actionHome);
  menuNavigation->addAction(m_actionGo);
  QMenu *menuAide = menuBar()->addMenu("?");
  menuAide->addAction(m_apropos);
  menuAide->addAction(m_apropos_qt);
}

void FenPrincipale::creerBarreOutils() {
  QToolBar *toolBarZnavigo = addToolBar("zNavigo Toolbar");
  toolBarZnavigo->addAction(m_actionPrecedente);
  toolBarZnavigo->addAction(m_actionSuivante);
  toolBarZnavigo->addAction(m_actionCancelLoad);
  toolBarZnavigo->addAction(m_actionRefresh);
  toolBarZnavigo->addAction(m_actionHome);
  m_URLfield = new QLineEdit();
  toolBarZnavigo->addWidget(m_URLfield);
  toolBarZnavigo->addAction(m_actionGo);
}

void FenPrincipale::creerZoneCentrale () {
    QWidget *zoneCentrale = new QWidget;
      QGridLayout *layoutOnglets = new QGridLayout();
        onglets = new QTabWidget();

          QWidget *page1 = new QWidget;
            QGridLayout *layout1 = new QGridLayout();
              QWebView *pageWeb = new QWebView;
              pageWeb->load(homepageUrl);
              m_URLfield->setText(homepageUrlText);
            layout1->addWidget(pageWeb, 0, 0);
          page1->setLayout(layout1);
          onglets->addTab(page1, "Page d'accueil");
          connect(pageWeb, SIGNAL(titleChanged(QString)), this, SLOT(updatePageTitle(QString)));
          connect(pageWeb, SIGNAL(loadProgress(int)), m_progressBar, SLOT(setValue(int)));
          connect(pageWeb, SIGNAL(loadProgress(int)), this, SLOT(setProgressTextLabel(int)));

      layoutOnglets->addWidget(onglets, 0, 0);
      zoneCentrale->setLayout(layoutOnglets);
    setCentralWidget(zoneCentrale);
}

void FenPrincipale::creerStatusBar () {
  QStatusBar *barreStatus = new QStatusBar;
    barreStatus->addWidget(m_progressBar);
    barreStatus->addWidget(m_labelProgressBar);
  setStatusBar(barreStatus);
}

void FenPrincipale::creerLiensSignauxSlots () {
  connect(m_actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
  connect(m_nouvelOnglet, SIGNAL(triggered()), this, SLOT(creationNouvelOnglet()));
  connect(m_fermerOnglet, SIGNAL(triggered()), this, SLOT(suppressionOngletActif()));
  connect(m_actionPrecedente, SIGNAL(triggered()), this, SLOT(pagePrecedenteOngletActuel()));
  connect(m_actionSuivante, SIGNAL(triggered()), this, SLOT(pageSuivanteOngletActuel()));
  connect(m_actionCancelLoad, SIGNAL(triggered()), this, SLOT(stopLoading()));
  connect(m_actionRefresh, SIGNAL(triggered()), this, SLOT(refreshPage()));
  connect(m_actionHome, SIGNAL(triggered()), this, SLOT(backHome()));
  connect(m_actionGo, SIGNAL(triggered()), this, SLOT(goToUrl()));
  connect(m_apropos_qt, SIGNAL(triggered()), this, SLOT(goToQt()));
  connect(m_apropos, SIGNAL(triggered()), this, SLOT(goToAPropos()));
  connect(onglets, SIGNAL(currentChanged(int)), this, SLOT(updateURLandTitle(int)));
}

void FenPrincipale::creationNouvelOnglet () {
  QWidget *nouvellePage = new QWidget;
    QGridLayout *layoutNouvellePage = new QGridLayout();
      QWebView *nouvellePageWeb = new QWebView;
      nouvellePageWeb->load(homepageUrl);
    layoutNouvellePage->addWidget(nouvellePageWeb, 0, 0);
  nouvellePage->setLayout(layoutNouvellePage);
  onglets->addTab(nouvellePage, "Nouvel onglet");
  connect(nouvellePageWeb, SIGNAL(titleChanged(QString)), this, SLOT(updatePageTitle(QString)));
  connect(nouvellePageWeb, SIGNAL(loadProgress(int)), this, SLOT(setProgressTextLabel(int)));
  connect(nouvellePageWeb, SIGNAL(loadProgress(int)), m_progressBar, SLOT(setValue(int)));
  onglets->setCurrentIndex(onglets->count() - 1);
}

void FenPrincipale::suppressionOngletActif() {
  if (onglets->count() > 1) {
    onglets->removeTab(onglets->currentIndex());
    QWebView *currentPage = pageActuelle();
    setWindowTitle(currentPage->title());
    QString urlAsString = currentPage->url().toString();
    m_URLfield->setText(urlAsString);
  } else {
    m_actionQuit->trigger();
  }
}

QWebView *FenPrincipale::pageActuelle()
{
    return onglets->currentWidget()->findChild<QWebView *>();
}

void FenPrincipale::pagePrecedenteOngletActuel() {
  QWebView *currentPage = pageActuelle();
  currentPage->back();
}

void FenPrincipale::pageSuivanteOngletActuel() {
    QWebView *currentPage = pageActuelle();
    currentPage->forward();
}

void FenPrincipale::updatePageTitle (QString newTitle) {
  setWindowTitle(newTitle);
  onglets->setTabText(onglets->currentIndex(), newTitle);
  QWebView *currentPage = pageActuelle();
  QString urlAsString = currentPage->url().toString();
  m_URLfield->setText(urlAsString);
}

void FenPrincipale::updateURLandTitle(int index) {
  QWebView *currentPage = pageActuelle();
  setWindowTitle(currentPage->title());
  QString urlAsString = currentPage->url().toString();
  m_URLfield->setText(urlAsString);
}

void FenPrincipale::stopLoading () {
  QWebView *currentPage = pageActuelle();
  currentPage->stop();
}

void FenPrincipale::refreshPage () {
  QWebView *currentPage = pageActuelle();
  currentPage->reload();
}

void FenPrincipale::backHome () {
  QWebView *currentPage = pageActuelle();
  currentPage->load(homepageUrl);
}

void FenPrincipale::goToUrl () {
  QWebView *currentPage = pageActuelle();
  // Attention, mettre l'URL complète, avec https et les www
  currentPage->load(m_URLfield->text());
  onglets->setTabText(onglets->currentIndex(), currentPage->title());
}

void FenPrincipale::goToQt () {
  QWebView *currentPage = pageActuelle();
  // Attention, mettre l'URL complète, avec https et les www
  currentPage->load(QUrl("https://doc.qt.io"));
  m_URLfield->setText("https://doc.qt.io/");
  onglets->setTabText(onglets->currentIndex(), currentPage->title());
}

void FenPrincipale::goToAPropos () {
  // Info cétait ici
    QMessageBox::information(this, tr("A propos..."), tr("zNavigo est un projet réalisé pour illustrer les tutoriels C++ du <a href=\"http://www.siteduzero.com\">Site du Zéro</a>.<br />Les images de ce programme ont été créées par <a href=\"http://www.everaldo.com\">Everaldo Coelho</a>"));
}

void FenPrincipale::setProgressTextLabel (int labelToUse) {
  QString label = QString::number(labelToUse) + "%";
  if (labelToUse != 100) {
    m_progressBar->setVisible(true);
    m_labelProgressBar->setText(label);
  } else {
    m_progressBar->setVisible(false);
    m_labelProgressBar->setText(QString("Terminé"));
  }
}
