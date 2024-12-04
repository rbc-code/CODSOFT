#include <QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QPushButton>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class ImageProcessor : public QMainWindow {
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Initialize UI
        QWidget *centralWidget = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout;

        imageLabel = new QLabel("Load an image to start");
        imageLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(imageLabel);

        QPushButton *loadButton = new QPushButton("Load Image");
        connect(loadButton, &QPushButton::clicked, this, &ImageProcessor::loadImage);
        layout->addWidget(loadButton);

        QPushButton *saveButton = new QPushButton("Save Image");
        connect(saveButton, &QPushButton::clicked, this, &ImageProcessor::saveImage);
        layout->addWidget(saveButton);

        QPushButton *grayscaleButton = new QPushButton("Grayscale");
        connect(grayscaleButton, &QPushButton::clicked, this, &ImageProcessor::applyGrayscale);
        layout->addWidget(grayscaleButton);

        QPushButton *blurButton = new QPushButton("Blur");
        connect(blurButton, &QPushButton::clicked, this, &ImageProcessor::applyBlur);
        layout->addWidget(blurButton);

        QPushButton *sharpenButton = new QPushButton("Sharpen");
        connect(sharpenButton, &QPushButton::clicked, this, &ImageProcessor::applySharpen);
        layout->addWidget(sharpenButton);

        QSlider *brightnessSlider = new QSlider(Qt::Horizontal);
        brightnessSlider->setRange(-100, 100);
        connect(brightnessSlider, &QSlider::valueChanged, this, &ImageProcessor::adjustBrightness);
        layout->addWidget(brightnessSlider);

        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);
    }

private slots:
    void loadImage() {
        QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.jpeg)");
        if (!filePath.isEmpty()) {
            image = cv::imread(filePath.toStdString());
            displayImage();
        }
    }

    void saveImage() {
        QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG Files (*.png);;JPEG Files (*.jpg)");
        if (!filePath.isEmpty()) {
            cv::imwrite(filePath.toStdString(), image);
        }
    }

    void applyGrayscale() {
        cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
        displayImage();
    }

    void applyBlur() {
        cv::GaussianBlur(image, image, cv::Size(5, 5), 0);
        displayImage();
    }

    void applySharpen() {
        cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
                          0, -1, 0,
                          -1, 5, -1,
                          0, -1, 0);
        cv::filter2D(image, image, image.depth(), kernel);
        displayImage();
    }

    void adjustBrightness(int value) {
        image.convertTo(image, -1, 1, value);
        displayImage();
    }

private:
    void displayImage() {
        if (!image.empty()) {
            cv::Mat rgb;
            cv::cvtColor(image, rgb, cv::COLOR_BGR2RGB);
            QImage qimg(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
            imageLabel->setPixmap(QPixmap::fromImage(qimg).scaled(imageLabel->size(), Qt::KeepAspectRatio));
        }
    }

    QLabel *imageLabel;
    cv::Mat image;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ImageProcessor window;
    window.resize(800, 600);
    window.show();
    return app.exec();
}