window.initMap = function (facilityCode) {
  const map = new google.maps.Map(document.getElementById("map"), {
    center: { lat: 37.86936, lng: 127.7288 },
    zoom: 11,
  });
  
  console.log(facilityCode);
  fetch(`/get_data?facilitycode=${facilityCode}`)
  .then(response => response.json())
  .then(data => {
    console.log(data);  // 서버로부터 받은 데이터 출력
    // 여기에서 받은 데이터를 사용하여 자바스크립트 작업을 수행
    console.log(Object.values(data)[0]);
    console.log(typeof(Object.values(data)[0][0]));

    const bounds = new google.maps.LatLngBounds();
    const infowindow = new google.maps.InfoWindow();
    let markerCount = 0; // 마커 개수를 추적하기 위한 변수 추가

    Object.values(data).forEach(({ address, facilities, latitude, longitude, operation_hours, phone ,code }) => {
      const marker = new google.maps.Marker({
        position: { lat : latitude, lng : longitude },
        map,
      });
      bounds.extend(marker.position);
      markerCount++; // 마커 추가할 때마다 카운트 증가
      

      marker.addListener("click", () => {
        let content_detail = `${facilities}<br>${address}<br>대관문의 : ${phone}<br>휴관일 : ${operation_hours}<br><a href="../facility/${code}">자세한 정보 보기</a>`;
        map.panTo(marker.position);
        infowindow.setContent(content_detail);
        infowindow.open({
          anchor: marker,
          map,
        });
      });

      // 마커가 하나뿐일 때만 최소 줌 설정
      if (markerCount === 1) {
        map.setCenter(marker.position);
        map.setZoom(14); // 원하는 최소 줌 레벨로 설정
      }
      else {
        map.fitBounds(bounds);
      }
    })
  })

  .catch(error => console.error('Error:', error));
}
