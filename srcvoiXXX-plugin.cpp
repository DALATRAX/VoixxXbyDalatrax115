#include <obs-module.h>
#include <obs-frontend-api.h>
#include <QMainWindow>
#include <QTimer>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialog>
#include <QApplication>
#include <QElapsedTimer>

// Dummy credenciales
const QString DUMMY_USER = "admin";
const QString DUMMY_PASS = "password";

// Clase principal del plugin
class VoiXXXPlugin : public QObject {
    Q_OBJECT

public:
    VoiXXXPlugin() : authenticated(false), premium(false), usageTimer(new QElapsedTimer()) {}
    ~VoiXXXPlugin() {}

    void authenticate() {
        bool ok;
        QString user = QInputDialog::getText(nullptr, "Autenticación", "Usuario:", QLineEdit::Normal, "", &ok);
        if (!ok || user != DUMMY_USER) return;

        QString pass = QInputDialog::getText(nullptr, "Autenticación", "Contraseña:", QLineEdit::Normal, "", &ok);
        if (!ok || pass != DUMMY_PASS) return;

        authenticated = true;
        usageTimer->start();
        startSubtitleTimer();
    }

    void checkGPUAccess() {
        // Simulación: Asumir acceso a GPU si OBS lo detecta
        bool hasGPU = obs_video_active(); // Dummy check
        QString subtitle = hasGPU ? "Plugin tiene acceso a GPU" : "Plugin NO tiene acceso a GPU";
        obs_frontend_add_event_callback([](enum obs_frontend_event event, void *private_data) {
            if (event == OBS_FRONTEND_EVENT_SCENE_CHANGED) {
                // Mostrar subtítulo en pantalla (usando source de texto)
                obs_source_t *source = obs_get_source_by_name("VOIXXX_Subtitle");
                if (source) {
                    obs_data_t *settings = obs_source_get_settings(source);
                    obs_data_set_string(settings, "text", subtitle.toUtf8().constData());
                    obs_source_update(source, settings);
                    obs_data_release(settings);
                }
            }
        }, nullptr);
    }

    void startSubtitleTimer() {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &VoiXXXPlugin::checkGPUAccess);
        timer->start(5000); // Cada 5 segundos
    }

    void checkUsageLimit() {
        if (!premium && usageTimer->elapsed() > 30000) { // 30 segundos
            showUpgradePrompt();
        }
    }

    void showUpgradePrompt() {
        QDialog dialog;
        dialog.setWindowTitle("Upgrade Requerido");
        QLabel *label = new QLabel("Se necesita upgrade a plan premium para continuar.");
        QPushButton *upgradeBtn = new QPushButton("Upgrade");
        connect(upgradeBtn, &QPushButton::clicked, this, &VoiXXXPlugin::upgradeToPremium);
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(label);
        layout->addWidget(upgradeBtn);
        dialog.setLayout(layout);
        dialog.exec();
    }

    void upgradeToPremium() {
        premium = true;
        QMessageBox::information(nullptr, "Upgrade", "¡Upgrade completado! Ahora tienes acceso premium.");
    }

private:
    bool authenticated;
    bool premium;
    QElapsedTimer *usageTimer;
};

// Funciones de OBS module
OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("voiXXX-plugin", "en-US")

bool obs_module_load(void) {
    VoiXXXPlugin *plugin = new VoiXXXPlugin();
    plugin->authenticate();
    // Timer para verificar límite de uso
    QTimer *usageTimer = new QTimer();
    connect(usageTimer, &QTimer::timeout, plugin, &VoiXXXPlugin::checkUsageLimit);
    usageTimer->start(1000); // Verificar cada segundo
    return true;
}

void obs_module_unload(void) {
    // Cleanup
}