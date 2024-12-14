<template>
  <div>
    <input type="text" v-model="query" @input="updateQuery" placeholder="Search by date or time..."/>
  </div>
</template>

<script>
export default {
  name: 'SearchComponent',
  data() {
    return {
      query: ''
    };
  },
  methods: {
    updateQuery() {
      this.$emit('search', this.query);
    }
  }
};
</script>

<style scoped>
input {
  padding: 12px;
  border: 1px solid #ccc;
  border-radius: 8px;
  font-size: 1em;
  width: 20%;
  box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.1);
  transition: border-color 0.25s;
}

input:focus {
  border-color: #646cff;
  outline: none;
}
</style>

