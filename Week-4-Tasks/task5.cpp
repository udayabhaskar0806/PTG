#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class ModeObserver {
public:
    virtual void update(const std::string& mode) = 0;
    virtual ~ModeObserver() {}
};

class HMISystem {
private:
    static HMISystem* instance;
    std::string mode;
    HMISystem() : mode("Day") {}
public:
    static HMISystem* getInstance() {
        if (instance == nullptr) {
            instance = new HMISystem();
        }
        return instance;
    }
    std::string getMode() const { return mode; }
    void setMode(const std::string& newMode) { mode = newMode; }
    void notifyObservers(const std::vector<ModeObserver*>& observers);
};

HMISystem* HMISystem::instance = nullptr;

void HMISystem::notifyObservers(const std::vector<ModeObserver*>& observers) {
    for (auto* observer : observers) {
        observer->update(mode);
    }
}

class Control {
public:
    virtual void display() = 0;
    virtual ~Control() {}
};

class ButtonControl : public Control, public ModeObserver {
public:
    void display() override {
        std::cout << "Displaying Button." << std::endl;
    }
    void update(const std::string& mode) override {
        std::cout << "Button updated to " << mode << " mode." << std::endl;
    }
};

class SliderControl : public Control, public ModeObserver {
public:
    void display() override {
        std::cout << "Displaying Slider." << std::endl;
    }
    void update(const std::string& mode) override {
        std::cout << "Slider updated to " << mode << " mode." << std::endl;
    }
};

class ControlFactory {
public:
    static Control* createControl(const std::string& type) {
        if (type == "button") {
            return new ButtonControl();
        } else if (type == "slider") {
            return new SliderControl();
        }
        return nullptr;
    }
};

class RenderingStrategy {
public:
    virtual void render() = 0;
    virtual ~RenderingStrategy() {}
};

class Render2D : public RenderingStrategy {
public:
    void render() override {
        std::cout << "Rendering in 2D." << std::endl;
    }
};

class Render3D : public RenderingStrategy {
public:
    void render() override {
        std::cout << "Rendering in 3D." << std::endl;
    }
};

class HMIContext {
private:
    RenderingStrategy* strategy;
public:
    HMIContext(RenderingStrategy* initialStrategy) : strategy(initialStrategy) {}
    void setStrategy(RenderingStrategy* newStrategy) {
        strategy = newStrategy;
    }
    void renderUI() {
        strategy->render();
    }
};

int main() {
    HMISystem* hmiSystem = HMISystem::getInstance();
    std::cout << "Current Mode: " << hmiSystem->getMode() << std::endl;
    hmiSystem->setMode("Night");
    std::cout << "Mode changed to: " << hmiSystem->getMode() << std::endl;

    Control* button = ControlFactory::createControl("button");
    Control* slider = ControlFactory::createControl("slider");

    button->display();
    slider->display();

    ButtonControl buttonWidget;
    SliderControl sliderWidget;
    std::vector<ModeObserver*> observers = { &buttonWidget, &sliderWidget };
    hmiSystem->notifyObservers(observers);

    Render2D render2D;
    Render3D render3D;
    HMIContext context(&render2D);
    
    context.renderUI();
    context.setStrategy(&render3D);
    context.renderUI();

    delete button;
    delete slider;

    return 0;
}
