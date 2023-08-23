#include "Delayer.h"
#include "Infos.h"
#include<unordered_map>
#include<chrono>
#include<random>

using namespace std::chrono_literals;
//Global Variables
unsigned int renderDelay = 1u;
unsigned int nbComparisons = 0u;
bool heapIsBuilt = false;
std::chrono::steady_clock::time_point start, end;
int renderID = -1;
bool isSorted = false;
int a = 0, b = 0, miniG = -1;
std::unordered_map<int, std::string> m{
    {0, "Insertion Sort"},
    { 1,"Bubble Sort" },
    { 2,"Selection Sort" },
    { 3,"Merge Sort" },
    { 4,"Heap Sort" },
    { 5,"Quick Sort" }

};
//Initializers
std::vector<Button*> initMainButtons() {
    std::vector<Button*> v;
    Button* insertionBtn = new Button(30.0f, 100.0f,200.0f,50.0f, "Insertion Sort"); v.push_back(insertionBtn);
    Button* selectionBtn = new Button(30.0f, 160.0f, 200.0f, 50.0f, "Selection Sort"); v.push_back(selectionBtn);
    Button* bubbleBtn = new Button(30.0f, 220.0f, 200.0f, 50.0f, "Bubble Sort"); v.push_back(bubbleBtn);
    Button* mergeBtn = new Button(30.0f, 280.0f, 200.0f, 50.0f, "Merge Sort"); v.push_back(mergeBtn);
    Button* heapBtn = new Button(30.0f, 340.0f, 200.0f, 50.0f, "Heap Sort"); v.push_back(heapBtn);
    Button* quickBtn = new Button(30.0f, 400.0f, 200.0f, 50.0f, "Quick Sort"); v.push_back(quickBtn);
    return v;
}
std::vector<Button*> initAlgoButtons() {
    std::vector<Button*> v(2);
    v[0] = new Button(10.0f, 10.0f, 100.0f, 50.0f, "Back");
    v[1] = new Button(690.0f, 10.0f, 100.0f, 50.0f, "Pause");
    return v;
}
std::vector<Infos*> initAlgoInfos() {
    std::vector<Infos*> v(2);
    v[0] = new Infos(20.0f, 120.0f, 0u,20u);
    v[1] = new Infos(20.0f, 160.0f, 0ms,20u);
    return v;
}
Delayer initDelayer() {
    Delayer delayer = Delayer(400.0f, 200.0f);
    return delayer;
}
void initBars(std::vector<sf::RectangleShape>& bars) {
    std::default_random_engine engine;
    std::uniform_int_distribution<int> distribution(0, 200);
    for (int i = 0; i < 160; i++) {
        float height = distribution(engine);
        float width = 5.0f;
        sf::RectangleShape bar(sf::Vector2f(width, height));
        bar.setPosition(sf::Vector2f(i * width, 580 - height));
        bar.setOutlineThickness(1);
        bar.setOutlineColor(sf::Color(169, 169, 169));
        bar.setFillColor(sf::Color::Black);
        bars[i] = bar;
    }
}
sf::Text* initText() {
    sf::Text* text = new sf::Text();
    text->setString("");
    sf::Font* font = new sf::Font();
    font->loadFromFile("Dosis-Bold.ttf");
    text->setFont(*font);
    return text;
}

//test
Delayer delayer = Delayer(340.0f, 200.0f);
//Updaters
void updateEvent(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window.close();
            exit(EXIT_SUCCESS);
        }
    }
}
void updateMainButtons(std::vector<Button*>& btns, sf::RenderWindow& window) {
    for (auto btn : btns)
        btn->update(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
    for (int i = 0; i < btns.size(); i++) {
        if (btns[i]->buttonPressed())
            renderID = i;
    }
}
void updateAlgoButtons(std::vector<Button*>& btns, sf::RenderWindow& window) {
    for (auto btn : btns)
        btn->update(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
    for (int i = 0; i < btns.size(); i++) {
        if (i == 0 && btns[i]->buttonPressed()) {
            renderID = -1;
            isSorted = false;
            delayer.setDelayTime(1u);
        }
    }
}
void updateInfos(std::vector<Infos*>& data) {
    data[0]->update(nbComparisons);
    end = !isSorted ? std::chrono::steady_clock::now() : end;
    std::chrono::milliseconds x = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    data[1]->update(x, renderDelay);
}
void updateDelayer(sf::RenderWindow& window) {
    delayer.update(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
    renderDelay = delayer.getDelayTime();
}
//Renderers
void drawBars(sf::RenderTarget& window, std::vector<sf::RectangleShape>& bars) {
    for (int i = 0; i < bars.size(); i++) {
        if (i == a) bars[i].setFillColor(sf::Color::Red);
        else if (i == b) bars[i].setFillColor(sf::Color::Green);
        else if (miniG != -1 && i == miniG) bars[i].setFillColor(sf::Color::Blue);
        else bars[i].setFillColor(sf::Color::Black);
        window.draw(bars[i]);
    }
}
void render(sf::RenderWindow& window,sf::RectangleShape& background,std::vector<sf::RectangleShape>& bars,  std::vector<Button*>& btns, sf::Text& title, std::vector<Infos*>& algoInfos) {
    sf::sleep(sf::milliseconds(renderDelay));
    updateEvent(window);
    updateAlgoButtons(btns, window);
    updateDelayer(window);
    updateInfos(algoInfos);
    
    title.setString(m[renderID]);
    title.setPosition(sf::Vector2f(
        background.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f, 30.0f
    ));
    window.clear();

    window.draw(background);
    for (Button* btn : btns) 
        btn->render(window);
    for (Infos* d : algoInfos)
        d->render(window);
    window.draw(title);
    delayer.render(window);
    drawBars(window, bars);
    window.display();
}
void renderMainState(sf::RenderWindow& window, sf::RectangleShape& background, std::vector<Button*>& btns, sf::Text& title) {
    updateEvent(window);
    updateMainButtons(btns, window);
    title.setString("Sorting Algorithms");
    title.setPosition(sf::Vector2f(
        background.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f, 50.0f
    ));
    window.clear();
    window.draw(background);
    window.draw(title);
    for (const auto& btn : btns)
        btn->render(window);
    window.display();
}

//Helpers
void deleteInitMainButtons(std::vector<Button*>& v) {
    for (auto btn : v) 
        delete btn;
}
void mySwap(std::vector<sf::RectangleShape>& bars, int i, int j) {
    std::swap(bars[i], bars[j]);
    float temp = bars[i].getPosition().x;
    bars[i].setPosition(sf::Vector2f(bars[j].getPosition().x, bars[i].getPosition().y));
    bars[j].setPosition(sf::Vector2f(temp, bars[j].getPosition().y));
}
bool COMPARE(const float& l, const float& r) {
    nbComparisons++;
    return l > r;
}

//Algorithms
void merge(std::vector<sf::RectangleShape>& bars, int l, int m, int r) {
    int i = l, j = m + 1;
    std::vector<float> temp;
    while (i <= m && j <= r) {
        if (COMPARE(bars[j].getSize().y, bars[i].getSize().y))
            temp.push_back(bars[i++].getSize().y);
        else temp.push_back(bars[j++].getSize().y);
    }
    while (j <= r)
        temp.push_back(bars[j++].getSize().y);
    while (i <= m)
        temp.push_back(bars[i++].getSize().y);
    int a = 0;
    for (int i = l; i <= r; i++) {
        bars[i].setSize(sf::Vector2f(bars[i].getSize().x, temp[a++]));
        bars[i].setPosition(sf::Vector2f(i * bars[i].getSize().x, 580 - bars[i].getSize().y));
    }
}
void mergeSort(sf::RenderWindow& window,int l,int r, sf::RectangleShape& background, std::vector<sf::RectangleShape>& bars, std::vector<Button*>& btns, sf::Text& title, std::vector<Infos*>& algoInfos) {
    if (renderID == -1) return;
    if (!isSorted) {
        if (l >= r) return;
        int m = l + (r - l) / 2;
        mergeSort(window, l, m, background, bars, btns, title, algoInfos);
        mergeSort(window, m+1, r, background, bars, btns, title, algoInfos);
        merge(bars, l, m, r);
        a = l; b = r;
        render(window,background, bars, btns, title, algoInfos);
    }
    else render(window, background, bars, btns, title, algoInfos);
    if (l == 0 && r == bars.size() - 1) isSorted = true;
}
void bubbleSort(sf::RenderWindow& window, sf::RectangleShape& background, std::vector<sf::RectangleShape>& bars, std::vector<Button*>& btns, sf::Text& title, std::vector<Infos*>& algoInfos) {
    if (!isSorted) {
        for (int pass = 0; pass < bars.size() - 1; pass++) {
            for (int i = 0; i < bars.size() - pass - 1; i++) {
                if (COMPARE(bars[i].getSize().y, bars[i + 1].getSize().y))
                    mySwap(bars, i, i + 1);
                if (renderID == -1) return;
                a = i; b = i + 1;
                render(window, background, bars, btns, title, algoInfos);
            }
        }
        isSorted = true;
    }
    else render(window, background, bars, btns, title, algoInfos);
}
void insertionSort(sf::RenderWindow& window, sf::RectangleShape& background, std::vector<sf::RectangleShape>& bars, std::vector<Button*>& btns, sf::Text& title, std::vector<Infos*>& algoInfos) {
    if (!isSorted) {
        for (int i = 1; i < bars.size(); i++) {
            int j = i - 1;
            while (j >= 0 && COMPARE(bars[j].getSize().y, bars[j+1].getSize().y)) {
                mySwap(bars, j, j + 1);
                if (renderID == -1) return;
                a = i; b = j;
                render(window,background, bars, btns, title, algoInfos);
                j--;
            }
        }
        isSorted = true;
    }
    else render(window, background, bars, btns, title, algoInfos);
}
void selectionSort(sf::RenderWindow& window, sf::RectangleShape& background, std::vector<sf::RectangleShape>& bars, std::vector<Button*>& btns, sf::Text& title, std::vector<Infos*>& algoInfos) {
    if (!isSorted) {
        for (int i = 0; i < bars.size() - 1; i++) {
            float mini = bars[i].getSize().y;
            int miniIndex = i;
            for (int j = i + 1; j < bars.size(); j++) {
                if (COMPARE(mini, bars[j].getSize().y)) {
                    mini = bars[j].getSize().y;
                    miniIndex = j;
                }
                if (renderID == -1) return;
                miniG = miniIndex; a = i; b = j;
                render(window, background, bars, btns, title, algoInfos);
            }
            mySwap(bars, i, miniIndex);
        }
        isSorted = true;
    }
    else render(window, background, bars, btns, title, algoInfos);
}
void heapify(sf::RenderWindow& window, sf::RectangleShape& background,int p, int n, std::vector<sf::RectangleShape>& bars, std::vector<Button*>& btns, sf::Text& title, std::vector<Infos*>& algoInfos) {
    if (renderID == -1) return;
    int left = 2 * p + 1;
    int right = 2 * p + 2;
    float maxi = p;
    if (left <= n && COMPARE(bars[left].getSize().y, bars[maxi].getSize().y)) maxi = left;
    if (right <= n && COMPARE(bars[right].getSize().y, bars[maxi].getSize().y)) maxi = right;
    if (maxi != p) {
        mySwap(bars, maxi, p);
        a = p; b = maxi;
        render(window, background, bars, btns, title, algoInfos);
        heapify(window, background, maxi, n,bars, btns, title, algoInfos);
    }
}
void buildHeap(sf::RenderWindow& window, sf::RectangleShape& background, std::vector<sf::RectangleShape>& bars, std::vector<Button*>& btns, sf::Text& title, std::vector<Infos*>& algoInfos) {
    for (int i = (bars.size() / 2) - 1; i >= 0; i--)
        heapify(window, background, i, bars.size()-1, bars, btns, title, algoInfos);
    heapIsBuilt = true;
}
void heapSort(sf::RenderWindow& window, sf::RectangleShape& background, std::vector<sf::RectangleShape>& bars, std::vector<Button*>& btns, sf::Text& title, std::vector<Infos*>& algoInfos) {
    if (!heapIsBuilt) {
        buildHeap(window, background, bars, btns,title,algoInfos);
        if (!isSorted) {
            for (int i = bars.size() - 1; i >= 0; i--) {
                mySwap(bars, 0, i);
                heapify(window, background, 0, i - 1, bars, btns, title, algoInfos);
            }
            isSorted = true;
        }
    }
    render(window, background, bars, btns, title, algoInfos);
}
void quickSort(sf::RenderWindow& window,int l,int r, sf::RectangleShape& background, std::vector<sf::RectangleShape>& bars, std::vector<Button*>& btns, sf::Text& title, std::vector<Infos*>& algoInfos) {
    if (renderID == -1) return;
    if (!isSorted) {
        if (l >= r) return;
        std::default_random_engine engine;
        std::uniform_int_distribution<int> dist(l, r);
        int pivotIndex = dist(engine);
        int pivot = bars[pivotIndex].getSize().y;
        mySwap(bars, l, pivotIndex);
        int i = l+1, j = r;
        while (i <= j) {
            while (i <= r && !COMPARE(bars[i].getSize().y, pivot)) i++;
            while (j >= l && COMPARE(bars[j].getSize().y, pivot)) j--;
            if (i < j) {
                mySwap(bars, i, j);
                i++; j--;
            }
            a = i; b = j; miniG = pivotIndex;
            render(window, background, bars, btns, title, algoInfos);
        }
        mySwap(bars, l, j);
        quickSort(window,l,j-1,background,bars,btns,title,algoInfos);
        quickSort(window, j+1, r, background, bars, btns, title, algoInfos);
    }
    else render(window, background, bars, btns, title, algoInfos);
    if (l == 0 && r == bars.size() - 1) isSorted = true;
}


//Main
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting algorithms");
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(sf::Color(178, 190, 181));
    sf::Event event;
    sf::Text* title = initText();
    std::vector<sf::RectangleShape> bars(160);
    initBars(bars);
    std::vector<Button*> mainBtns = initMainButtons();
    std::vector<Button*> algoBtns = initAlgoButtons();
    std::vector<Infos*> algoInfos = initAlgoInfos();

    while (window.isOpen()) {
        updateEvent(window);
        if (!isSorted || renderID == -1) {
            bars = std::vector<sf::RectangleShape>(160);
            initBars(bars);
            heapIsBuilt = false;
            isSorted = false;
            miniG = -1;
            nbComparisons = 0;
            start = std::chrono::steady_clock::now();
        }
        
        switch (renderID) {
        case -1: {
            renderMainState(window, background, mainBtns, *title);
            end = std::chrono::steady_clock::now();
        }
                break;
            case 0: insertionSort(window,background,bars,algoBtns,*title,algoInfos); break;
            case 1: selectionSort(window, background, bars, algoBtns, *title, algoInfos); break;
            case 2: bubbleSort(window, background, bars, algoBtns, *title, algoInfos); break;
            case 3: mergeSort(window,0,bars.size()-1, background, bars, algoBtns, *title, algoInfos); break;
            case 4: heapSort(window, background, bars, algoBtns, *title, algoInfos); break;
            case 5: quickSort(window,0,bars.size()-1, background, bars, algoBtns, *title, algoInfos); break;
            default: exit(EXIT_SUCCESS);
        }
    }
    delete title;
    deleteInitMainButtons(mainBtns);
    deleteInitMainButtons(algoBtns);
    return 0;
}