<template>
  <div id="app">
    <SearchComponent @search="handleSearch" />
    <TableComponent :records="paginatedRecords" />
    <PaginationComponent 
      :totalRecords="filteredRecords.length" 
      :recordsPerPage="recordsPerPage" 
      :currentPage="currentPage" 
      @changePage="handlePageChange" />
  </div>
</template>

<script>
import TableComponent from './components/TableComponent.vue';
import SearchComponent from './components/SearchComponent.vue';
import PaginationComponent from './components/PaginationComponent.vue';

export default {
  name: 'App',
  components: {
    TableComponent,
    SearchComponent,
    PaginationComponent
  },
  data() {
    return {
      records: [],
      searchQuery: '',
      currentPage: 1,
      recordsPerPage: 30
    };
  },
  computed: {
    filteredRecords() {
      return this.records.filter(record => {
        const query = this.searchQuery.toLowerCase();
        return (
          record.date.toLowerCase().includes(query) ||
          record.time.toLowerCase().includes(query) ||
          record.farm_name.toLowerCase().includes(query)
        );
      });
    },
    paginatedRecords() {
      const start = (this.currentPage - 1) * this.recordsPerPage;
      const end = start + this.recordsPerPage;
      return this.filteredRecords.slice(start, end);
    }
  },
  methods: {
    async fetchRecords() {
      try {
        const response = await fetch('http://192.168.0.108:8000/records/');
        if (response.ok) {
          const data = await response.json();
          this.records = data.map(record => ({
            id: record.id,
            farm_name: record.Farm_Name,
            temp: record.Air_Temperature,
            pressure: record.Pressure,
            humidity: record.Humidity,
            CO2: record.CO2,
            TVOC: record.TVOC,
            soil_temperature: record.Soil_Temperature,
            soil_humidity: record.Soil_Humidity,
            illumination: record.Illumination,
            time: record.Time,
            date: record.Date
          }));
        } else {
          console.error('Error fetching records:', response.statusText);
        }
      } catch (error) {
        console.error('Error fetching records:', error);
      }
    },
    handleSearch(query) {
      this.searchQuery = query;
      this.currentPage = 1;
    },
    handlePageChange(newPage) {
      this.currentPage = newPage;
    }
  },
  created() {
    this.fetchRecords();
  }
};
</script>

<style>
</style>
