#pragma once

class Sprite
{
private:
	int hFrames, vFrames;
	const ltex_t* tex;
	lblend_t mode;
	float r, g, b, a;
	float angle;
	vec2 position, scale, pivot;
	int FPS, frame;
	int speed;
	float displayTimeSeconds;


public:
	Sprite() { }
	~Sprite() { printf("Sprite obj deleted."); }
	
	typedef void(*CallbackFunc)(Sprite& _Sprite, float _DeltaTime);
	
	Sprite(const ltex_t* _Tex) : hFrames(1), vFrames(1)
	{
		tex = _Tex;
	}

	// GETTERS
	const ltex_t* GetTexture() const { return tex; }
	lblend_t GetBlend() const; // @TODO:
	void* GetUserData(); // @TODO:
	float GetRed() const { return r; }
	float GetGreen() const { return g; }
	float GetBlue() const { return b; }
	float GetAlpha() const { return a; }
	const vec2& GetPosition() const { return position; }
	float GetAngle() const { return angle; }
	const vec2& GetScale() const { return scale; }
	vec2 GetSize() const; // @TODO:
	const vec2& GetPivot() const; // @TODO:
	int GetHFrames() const { return hFrames; }
	int GetVframes() const { return vFrames; }
	int GetFPS() const { return FPS; }
	float GetCurrentFrame() const { return frame; }
	int GetSpeed() { return speed; }

	// SETTERS
	void SetTexture(const ltex_t* _Tex, int _HFrames, int _VFrames);
	void SetBlend(lblend_t _Mode) { mode = _Mode; }
	void SetUserData(void* _Data);
	void SetColor(float _R, float _G, float _B, float _A);
	void SetPosition(const vec2& _Position) { position = _Position; }
	void SetAngle(float _Angle) { angle = _Angle; }
	void SetScale(const vec2& _Scale) { scale = _Scale; }
	void SetPivot(const vec2& _Pivot) { pivot = _Pivot; }
	void SetFPS(int _FPS); // @TODO:
	void SetCurrentFrame(int _Frame) { frame = _Frame; }
	void SetSpeed(int _Speed) { speed = _Speed; }

	// FUNCTIONS 
	void Update(float _DeltaTime);
	void Draw() const;
	void SetCallback(CallbackFunc func);
};