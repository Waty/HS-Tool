class IGObj
{
	~IGObj() = default;

public:
	virtual void Update() { }
};

class IUIMsgHandler
{
	~IUIMsgHandler() = default;

public:
	virtual void OnKey(unsigned int wParam, unsigned int lParam) = 0;

	virtual int OnSetFocus(int) = 0;
	virtual void OnMouseButton(unsigned int msg, unsigned int wParam, int rx, int ry) = 0;
	virtual int OnMouseMove(int rx, int ry) = 0;
	virtual int OnMouseWheel(int, int, int) = 0;
	virtual void OnMouseEnter(bool bEnter) = 0;
	virtual void OnDraggableMove(int, void*, int, int) = 0;
	virtual void SetEnable(bool bEnable) = 0;
	virtual bool IsEnabled() = 0;
	virtual void SetShow(bool bShow) = 0;
	virtual bool IsShown() = 0;
};

class ZRefCounted
{
public:
	union
	{
		long _m_nRef;
		ZRefCounted* _m_pNext;
	};

	ZRefCounted* _m_pPrev;

	bool IsLastRef()
	{
		return false;
	} // dummy

protected:
	virtual ~ZRefCounted() { } // dummy
	ZRefCounted() { } // dummy
};

class CWnd : public IGObj, public IUIMsgHandler, public ZRefCounted {};

class CWndMan : public CWnd {};