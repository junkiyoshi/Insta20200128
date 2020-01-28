#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->font_size = 15;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	vector<string> word_list = { "PCD TOKYO 2020 !", "PCD TOKYO 2020 !", "PCD TOKYO 2020 !", "PCD TOKYO 2020 !" };
	int sample_count = 180;
	for (auto& word : word_list) {

		auto noise_param = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

		auto word_size = this->font.getStringBoundingBox(word, 0, 0);
		vector<ofPath> word_path = this->font.getStringAsPoints(word, true, false);
		for (int word_index = 0; word_index < word_path.size(); word_index++) {

			vector<ofPolyline> outline = word_path[word_index].getOutline();

			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
				for (auto& vertex : vertices) {

					auto noise_location = glm::vec3(
						ofMap(ofNoise(noise_param.x, vertex.x * 0.005 - ofGetFrameNum() * 0.005), 0, 1, -300, 300),
						ofMap(ofNoise(noise_param.y, vertex.x * 0.005 - ofGetFrameNum() * 0.005), 0, 1, -300, 300),
						ofMap(ofNoise(noise_param.z, vertex.x * 0.005 - ofGetFrameNum() * 0.005), 0, 1, -300, 300));

					ofVertex(noise_location + vertex - glm::vec3(word_size.getWidth() * 0.5, -word_size.getHeight() * 0.5, 0));
				}
			}
			ofEndShape();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}