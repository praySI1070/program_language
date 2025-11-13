자주 쓸 거 같은거
----------

타입 판단

      component.is('text')

돔 태그 판단

      component.attributes.tagName === 'div'

자식 전부 순회

      function traverse(component) {
      
          const children = component.components().models;
          children.forEach(child => {
              traverse(child); // 자식도 재귀 순회
          });
      }

      // 최상위 컴포넌트들 가져오기
      const rootComponents = editor.getComponents().models;
      
      rootComponents.forEach(cmp => {
      traverse(cmp);
      });

스타일 추가

      component.addStyle({})

스타일 변화

      component.setStyle({})

wrapper 반환 ( 컴포넌트 반환)

      const wrapper = editor.getWrapper();

html 요소중에 body 반환 (html요소 반환)

      const canvasBody = editor.Canvas.getBody();

find로 조건맞는 컴포넌트 반환 (.global은 css 명) (배열 반환이라 [0])

      const test = wrapper.find('.global_container_')[0];

컴포넌트의 html 요소 반환 (view.el)

      const CS = component.view.el;

