<template>
  <div>
    <table class="styled-table">
      <thead>
        <tr>
          <th @mouseover="showTooltip('ID', $event)" @mouseleave="hideTooltip">ID</th>
          <th @mouseover="showTooltip('Название фермы', $event)" @mouseleave="hideTooltip">Название Фермы</th>
          <th @mouseover="showTooltip('Температура воздуха (°C)', $event)" @mouseleave="hideTooltip">Температура</th>
          <th @mouseover="showTooltip('Давление (hPa)', $event)" @mouseleave="hideTooltip">Давление</th>
          <th @mouseover="showTooltip('Влажность (%)', $event)" @mouseleave="hideTooltip">Влажность</th>
          <th @mouseover="showTooltip('CO2 (ppm)', $event)" @mouseleave="hideTooltip">CO2</th>
          <th @mouseover="showTooltip('TVOC (ppb)', $event)" @mouseleave="hideTooltip">TVOC</th>
          <th @mouseover="showTooltip('Температура почвы (°C)', $event)" @mouseleave="hideTooltip">Температура почвы</th>
          <th @mouseover="showTooltip('Влажность почвы (%)', $event)" @mouseleave="hideTooltip">Влажность почвы</th>
          <th @mouseover="showTooltip('Освещенность (lux)', $event)" @mouseleave="hideTooltip">Освещенность</th>
          <th @mouseover="showTooltip('Время', $event)" @mouseleave="hideTooltip">Время</th>
          <th @mouseover="showTooltip('Дата', $event)" @mouseleave="hideTooltip">Дата</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="record in records" :key="record.id">
          <td>{{ record.id }}</td>
          <td>{{ record.farm_name }}</td>
          <td>{{ record.temp }}</td>
          <td>{{ record.pressure }}</td>
          <td>{{ record.humidity }}</td>
          <td>{{ record.CO2 }}</td>
          <td>{{ record.TVOC }}</td>
          <td>{{ record.soil_temperature }}</td>
          <td>{{ record.soil_humidity }}</td>
          <td>{{ record.illumination }}</td>
          <td>{{ record.time }}</td>
          <td>{{ record.date }}</td>
        </tr>
      </tbody>
    </table>
    <div v-if="tooltip.visible" :style="{ top: tooltip.y + 'px', left: tooltip.x + 'px' }" class="tooltip">
      {{ tooltip.text }}
    </div>
  </div>
</template>

<script>
export default {
  name: 'TableComponent',
  props: {
    records: {
      type: Array,
      required: true
    }
  },
  data() {
    return {
      tooltip: {
        visible: false,
        text: '',
        x: 0,
        y: 0
      }
    };
  },
  methods: {
    showTooltip(text, event) {
      this.tooltip.text = text;
      this.tooltip.x = event.pageX + 10;
      this.tooltip.y = event.pageY + 10;
      this.tooltip.visible = true;
    },
    hideTooltip() {
      this.tooltip.visible = false;
    }
  }
};
</script>

<style scoped>
.styled-table {
  width: 100%;
  border-collapse: collapse;
  margin: 20px 0;
  font-size: 16px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
  border-radius: 8px;
  overflow: hidden;
}

.styled-table th, .styled-table td {
  padding: 12px;
  text-align: center;
}

.styled-table thead {
  background-color: #4CAF50;
  color: white;
}

.styled-table tbody tr:nth-child(even) {
  background-color: #f2f2f2;
}

.styled-table tbody tr:hover {
  background-color: #e0e0e0;
}

.styled-table th {
  font-weight: bold;
  text-transform: uppercase;
}

.styled-table td {
  font-size: 14px;
}

.styled-table tr {
  transition: background-color 0.3s ease;
}

.styled-table tr:hover td {
  color: #fff;
}

.styled-table tr:nth-child(odd):hover {
  background-color: #81c784;
}

.tooltip {
  position: absolute;
  background-color: rgba(0, 0, 0, 0.7);
  color: white;
  padding: 5px;
  border-radius: 5px;
  font-size: 12px;
  pointer-events: none;
  z-index: 1000;
}
</style>
