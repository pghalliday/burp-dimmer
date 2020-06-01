#ifndef Redux_State_State_hpp
#define Redux_State_State_hpp

namespace Redux {
  class State {
    public:

      static const State * replace(const State * previous, const State * next) {
        delete previous;
        return next;
      }

      template <class DerivedState>
      const DerivedState * as() const {
        return static_cast<const DerivedState *>(this);
      }

  };
}

#endif
