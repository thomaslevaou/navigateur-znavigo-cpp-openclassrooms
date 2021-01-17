#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtWidgets>
#include <QtWebKitWidgets>


/* Dans la plupart des gros projets, la fenêtre principale est un Widget héritant
* de QMainWindow */
class FenPrincipale : public QMainWindow
{
    Q_OBJECT

    public:
      FenPrincipale();
      void creerActions();
      void creerMenus();
      void creerBarreOutils();
      void creerZoneCentrale();
      void creerStatusBar();
      void creerLiensSignauxSlots();
      QWebView* pageActuelle();

    public slots:
      void creationNouvelOnglet();
      void suppressionOngletActif();
      void pagePrecedenteOngletActuel();
      void pageSuivanteOngletActuel();
      void updatePageTitle(QString newTitle);
      void stopLoading();
      void refreshPage();
      void backHome();
      void goToUrl();
      void goToQt();
      void goToAPropos();
      void setProgressTextLabel(int labelToUse);
      void updateURLandTitle(int index);

    private:
      QAction *m_actionPrecedente;
      QAction *m_actionSuivante;
      QAction *m_actionCancelLoad;
      QAction *m_actionRefresh;
      QAction *m_actionHome;
      QAction *m_actionQuit;
      QAction *m_nouvelOnglet;
      QAction *m_fermerOnglet;
      QAction *m_apropos;
      QAction *m_apropos_qt;
      QLineEdit *m_URLfield;
      QAction *m_actionGo;
      QTabWidget *onglets;
      QProgressBar *m_progressBar;
      QLabel *m_labelProgressBar;
      QUrl homepageUrl;
      QString homepageUrlText;
};

#endif
