<template>
    <div class="pagination">
      <button :disabled="currentPage === 1" @click="changePage(currentPage - 1)">&#8592;</button>
      <span>Страница {{ currentPage }} из {{ totalPages }}</span>
      <button :disabled="currentPage === totalPages" @click="changePage(currentPage + 1)">&#8594;</button>
    </div>
  </template>
  
  <script>
  export default {
    props: {
      totalRecords: Number,
      recordsPerPage: Number,
      currentPage: Number
    },
    computed: {
      totalPages() {
        return Math.ceil(this.totalRecords / this.recordsPerPage);
      }
    },
    methods: {
      changePage(page) {
        this.$emit('changePage', page);
      }
    }
  };
  </script>
  
  <style scoped>
  .pagination {
    display: flex;
    justify-content: center;
    align-items: center;
    margin: 20px 0;
  }
  
  button {
    padding: 8px 16px;
    margin: 0 8px;
    font-size: 1em;
    border: none;
    background-color: #4caf50;
    color: white;
    cursor: pointer;
    border-radius: 4px;
  }
  
  button:disabled {
    background-color: #ddd;
    cursor: not-allowed;
  }
  
  span {
    font-size: 1em;
  }
  </style>
  