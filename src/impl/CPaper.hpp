#if !defined(EXPERIMENT_CPAPER_HPP)
#define EXPERIMENT_CPAPER_HPP 1

#include "com/Guid.hpp"
#include "interface/IUnknown.hpp"
#include "interface/IDrawable.hpp"

namespace HIT
{
  class CPaper : public IDrawable
  {
  public:
    CPaper()
    {
      m_nRefCount = 1;
    }

  public:
    virtual void draw() override;

  public:
    virtual int queryInterface(const RefIID iid, void **ppvInterface) override
    {
      if (HIT::isIUnknown(iid))
      {
        *ppvInterface = reinterpret_cast<IUnknown *> (this);
        addRef();
        return 0;
      }
      else if (iid == IID_IDrawable)
      {
        *ppvInterface = reinterpret_cast<IDrawable *> (this);
        addRef();
        return 0;
      }
      else
      {
        *ppvInterface = nullptr;
        return 1;
      }
    }

    virtual int addRef() override
    {
      m_nRefCount++;
    }

    virtual int release() override
    {
      m_nRefCount--;

      if (m_nRefCount == 0)
        delete this;
    }

  private:
    int m_nRefCount;
  };
}

#endif // EXPERIMENT_CPAPER_HPP
