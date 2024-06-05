#pragma once

class Score {

public:

	static Score& intstance() {
		static Score* instance = new Score();
		return *instance;
	}

	Score(Score& other) = delete;
	void operator=(const Score&) = delete;
	int score = 0;

private:
	Score() {}
};






